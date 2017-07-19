#pragma once

// Typedefs
typedef char int8;
typedef short int int16;
typedef long int int64;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint;
typedef unsigned long int uint64;

// Casting
#define FLOAT_S(VALUE) static_cast<float>(VALUE)
#define FLOAT_R(VALUE) reinterpret_cast<float>(VALUE)
#define FLOAT_D(VALUE) dynamic_cast<float>(VALUE)
#define FLOAT_C(VALUE) const_cast<float>(VALUE)

#define INT_S(VALUE) static_cast<int>(VALUE)
#define INT_R(VALUE) reinterpret_cast<int>(VALUE)
#define INT_D(VALUE) dynamic_cast<int>(VALUE)
#define INT_C(VALUE) const_cast<int>(VALUE)

#define UINT_S(VALUE) static_cast<uint>(VALUE)
#define UINT_R(VALUE) reinterpret_cast<uint>(VALUE)
#define UINT_D(VALUE) dynamic_cast<uint>(VALUE)
#define UINT_C(VALUE) const_cast<uint>(VALUE)

#define DOUBLE_S(VALUE) static_cast<double>(VALUE)
#define DOUBLE_R(VALUE) reinterpret_cast<double>(VALUE)
#define DOUBLE_D(VALUE) dynamic_cast<double>(VALUE)
#define DOUBLE_C(VALUE) const_cast<double>(VALUE)