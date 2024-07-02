//
// Created by 着魔之人 on 24-6-18.
//

#ifndef MY_WEBSERVER_STRING_PIECE_H
#define MY_WEBSERVER_STRING_PIECE_H

#include "base/types.h"
#include <iosfwd>

class StringArg {
public:
    explicit StringArg(const char *str) : str_(str) {}

    explicit StringArg(const string &str) : str_(str.c_str()) {}

    [[nodiscard]] const char *c_str() const { return str_; }

private:
    const char *str_;
};

class StringPiece {
private:
    const char *ptr_;
    int length_{};

public:
    StringPiece() : ptr_(nullptr), length_(0) {}

    explicit StringPiece(const char *str)
            : ptr_(str), length_(static_cast<int>(strlen(str))) {}

    explicit StringPiece(const string &str) : ptr_(str.data()) {}

    StringPiece(const char *offset, int len) : ptr_(offset), length_(len) {}

    char operator[](int i) const { return ptr_[i]; }

    [[nodiscard]] int size() const { return length_; }

    [[nodiscard]] bool empty() const { return length_ == 0; }

    [[nodiscard]] const char *begin() const { return ptr_; }

    [[nodiscard]] const char *end() const { return ptr_ + length_; }

    void clear() {
        ptr_ = nullptr;
        length_ = 0;
    }

    [[nodiscard]] const char *data() const { return ptr_; }
};

#ifdef HAVE_TYPE_TRAITS
// This makes vector<StringPiece> really fast for some STL implementations
template <> struct __type_traits<muduo::StringPiece> {
  typedef __true_type has_trivial_default_constructor;
  typedef __true_type has_trivial_copy_constructor;
  typedef __true_type has_trivial_assignment_operator;
  typedef __true_type has_trivial_destructor;
  typedef __true_type is_POD_type;
};
#endif

#endif // MY_WEBSERVER_STRING_PIECE_H
