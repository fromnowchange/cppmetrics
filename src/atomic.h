
/**
 * (C) 2010-2011 Alibaba Group Holding Limited.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * Version: $Id$
 *
 * ob_atomic.h for ...
 *
 * Authors:
 *   qushan <qushan@taobao.com>
 *
 */

#include <stdint.h>

#ifndef  _METRICS__ATOMIC_H_
#define  _METRICS__ATOMIC_H_

namespace com
{
namespace xiaomi
{
namespace mfs
{
namespace metrics
{
// Proclaim we are using SMP
#ifndef CONFIG_SMP
# define CONFIG_SMP
#endif

#if defined(__i386__) || defined(__x86_64__)

// Atomic operations that C can't guarantee us.  Useful for
// resource counting etc..
// SMP lock prefix
#ifdef CONFIG_SMP
#define LOCK_PREFIX "lock ; "
#else
#define LOCK_PREFIX ""
#endif

//return: the incremented value;
/// 原子地做 8位，16位，32位，64位的++i的操作
/// 该操作虽然参数和返回值都是无符号型整数，但是一样可以
/// 对有符号型整数做操作，只需要做适当的参数转换即可
/// @param pv 指向操作数的指针
/// @return 操作数加1以后的数值
#ifdef __x86_64__
static __inline__ uint64_t atomic_inc(volatile uint64_t * pv)
{
    register unsigned long __res;
    __asm__ __volatile__ (
            "movq $1,%0;"
            LOCK_PREFIX "xaddq %0,(%1);"
            "incq %0"
            :"=a" (__res), "=q" (pv): "1" (pv));
    return __res;
}
#endif

static __inline__ uint32_t atomic_inc(volatile uint32_t * pv)
{
    register unsigned int __res;
    __asm__ __volatile__ (
            "movl $1,%0;"
            LOCK_PREFIX "xaddl %0,(%1);"
            "incl %0"
            :"=a" (__res), "=q" (pv): "1" (pv));
    return __res;
}

static __inline__ uint16_t atomic_inc(volatile uint16_t * pv)
{
    register unsigned short __res;
    __asm__ __volatile__ (
            "movw $1,%0;"
            LOCK_PREFIX "xaddw %0,(%1);"
            "incw %0"
            :"=a" (__res), "=q" (pv): "1" (pv));
    return __res;

}

static __inline__ uint8_t atomic_inc(volatile uint8_t * pv)
{
    register unsigned char __res;
    __asm__ __volatile__ (
            "movb $1,%0;"
            LOCK_PREFIX "xaddb %0,(%1);"
            "incb %0"
            :"=a" (__res), "=q" (pv): "1" (pv));
    return __res;
}

//return: the decremented value;
/// 原子地做 8位，16位，32位，64位的--i的操作
/// 该操作虽然参数和返回值都是无符号型整数，但是一样可以
/// 对有符号型整数做操作，只需要做适当的参数转换即可
/// @param pv 指向操作数的指针
/// @return 操作数减1后的数值
#ifdef __x86_64__
static __inline__ uint64_t atomic_dec(volatile uint64_t * pv)
{
    register unsigned long __res;
    __asm__ __volatile__ (
            "movq $0xffffffffffffffff,%0;"
            LOCK_PREFIX "xaddq %0,(%1);"
            "decq %0"
            : "=a" (__res), "=q" (pv): "1" (pv));
    return __res;

}
#endif
static __inline__ uint32_t atomic_dec(volatile uint32_t * pv)
{
    register unsigned int __res;
    __asm__ __volatile__ (
            "movl $0xffffffff,%0;"
            LOCK_PREFIX "xaddl %0,(%1);"
            "decl %0"
            : "=a" (__res), "=q" (pv): "1" (pv));
    return __res;

}
static __inline__ uint16_t atomic_dec(volatile uint16_t * pv)
{
    register unsigned short __res;
    __asm__ __volatile__ (
            "movw $0xffff,%0;"
            LOCK_PREFIX "xaddw %0,(%1);"
            "decw %0"
            : "=a" (__res), "=q" (pv): "1" (pv));
    return __res;
}

static __inline__ uint8_t atomic_dec(volatile uint8_t * pv)
{
    register unsigned char __res;
    __asm__ __volatile__ (
            "movb $0xff,%0;"
            LOCK_PREFIX "xaddb %0,(%1);"
            "decb %0"
            : "=a" (__res), "=q" (pv): "1" (pv));
    return __res;
}

//return: the initial value of *pv
/// 原子地做 8位，16位，32位，64位的加法的操作
/// 该操作虽然参数和返回值都是无符号型整数，但是一样可以
/// 对有符号型整数做操作，只需要做适当的参数转换即可
/// @param pv 指向操作数的指针
/// @return 操作数加法之前的数值
#ifdef __x86_64__
static __inline__ uint64_t atomic_add(volatile uint64_t * pv, const uint64_t av)
{
    //:"=a" (__res), "=q" (pv): "m"(av), "1" (pv));
    register unsigned long __res;
    __asm__ __volatile__ (
            "movq %2,%0;"
            LOCK_PREFIX "xaddq %0,(%1);"
            :"=a" (__res), "=q" (pv): "mr"(av), "1" (pv));
    return __res;
}
#endif
static __inline__ uint32_t atomic_add(volatile uint32_t * pv, const uint32_t av)
{
    //:"=a" (__res), "=q" (pv): "m"(av), "1" (pv));
    register unsigned int __res;
    __asm__ __volatile__ (
            "movl %2,%0;"
            LOCK_PREFIX "xaddl %0,(%1);"
            :"=a" (__res), "=q" (pv): "mr"(av), "1" (pv));
    return __res;
}

static __inline__ uint16_t atomic_add(volatile uint16_t * pv, const uint16_t av)
{
    //:"=a" (__res), "=q" (pv): "m"(av), "1" (pv));
    register unsigned short __res;
    __asm__ __volatile__ (
            "movw %2,%0;"
            LOCK_PREFIX "xaddw %0,(%1);"
            :"=a" (__res), "=q" (pv): "mr"(av), "1" (pv));
    return __res;
}

static __inline__ uint8_t atomic_add(volatile uint8_t * pv, const uint8_t av)
{
    //:"=a" (__res), "=q" (pv): "m"(av), "1" (pv));
    register unsigned char __res;
    __asm__ __volatile__ (
            "movb %2,%0;"
            LOCK_PREFIX "xaddb %0,(%1);"
            :"=a" (__res), "=q" (pv): "mr"(av), "1" (pv));
    return __res;
}

//function: set *pv to nv
//return: the initial value of *pv
/// 原子地把nv赋值给pv指向的整数，支持8位，16位，32位，64位操作
/// @param pv 待赋值的整数（目的操作数）
/// @param nv 向pv赋的整数
/// @return pv指向的赋值前的数值
#ifdef __x86_64__
static __inline__ uint64_t atomic_exchange(volatile uint64_t * pv, const uint64_t nv)
{
    register unsigned long __res;
    __asm__ __volatile__ (
            "1:"
            LOCK_PREFIX "cmpxchgq %3,(%1);"
            "jne 1b":
            "=a" (__res), "=q" (pv): "1" (pv), "q" (nv), "0" (*pv));
    return __res;
}
#endif
static __inline__ uint32_t atomic_exchange(volatile uint32_t * pv, const uint32_t nv)
{
    register unsigned int __res;
    __asm__ __volatile__ (
            "1:"
            LOCK_PREFIX "cmpxchgl %3,(%1);"
            "jne 1b":
            "=a" (__res), "=q" (pv): "1" (pv), "q" (nv), "0" (*pv));
    return __res;
}

static __inline__ uint16_t atomic_exchange(volatile uint16_t * pv, const uint16_t nv)
{
    register unsigned short __res;
    __asm__ __volatile__ (
            "1:"
            LOCK_PREFIX "cmpxchgw %3,(%1);"
            "jne 1b":
            "=a" (__res), "=q" (pv): "1" (pv), "q" (nv), "0" (*pv));
    return __res;
}

static __inline__ uint8_t atomic_exchange(volatile uint8_t * pv, const uint8_t nv)
{
    register unsigned char __res;
    __asm__ __volatile__ (
            "1:"
            LOCK_PREFIX "cmpxchgb %3,(%1);"
            "jne 1b":
            "=a" (__res), "=q" (pv): "1" (pv), "q" (nv), "0" (*pv));
    return __res;
}

//function: compare *pv to cv, if equal, set *pv to nv, otherwise do nothing.
//return: the initial value of *pv
/// 比较pv和cv，如果两者相等，则返回pv原有数值并且把nv赋值给pv
/// 否则什么也不作，返回pv原有数值
/// @param pv 待赋值的整数（目的操作数）
/// @param nv 向pv赋的整数
/// @param cv 和pv比较的整数
/// @return pv指向的操作前的数值
#ifdef __x86_64__
static __inline__ uint64_t atomic_compare_exchange(volatile uint64_t * pv, const uint64_t nv, const uint64_t cv)
{
    register unsigned long __res;
    __asm__ __volatile__ (
            LOCK_PREFIX "cmpxchgq %3,(%1)"
            : "=a" (__res), "=q" (pv) : "1" (pv), "q" (nv), "0" (cv));
    return __res;
}
#endif
static __inline__ uint32_t atomic_compare_exchange(volatile uint32_t * pv, const uint32_t nv, const uint32_t cv)
{
    register unsigned int __res;
    __asm__ __volatile__ (
            LOCK_PREFIX "cmpxchgl %3,(%1)"
            : "=a" (__res), "=q" (pv) : "1" (pv), "q" (nv), "0" (cv));
    return __res;
}
static __inline__ uint16_t atomic_compare_exchange(volatile uint16_t * pv, const uint16_t nv, const uint16_t cv)
{
    register unsigned short __res;
    __asm__ __volatile__ (
            LOCK_PREFIX "cmpxchgw %3,(%1)"
            : "=a" (__res), "=q" (pv) : "1" (pv), "q" (nv), "0" (cv));
    return __res;
}
static __inline__ uint8_t atomic_compare_exchange(volatile uint8_t * pv, const uint8_t nv, const uint8_t cv)
{
    register unsigned char __res;
    __asm__ __volatile__ (
            LOCK_PREFIX "cmpxchgb %3,(%1)"
            : "=a" (__res), "=q" (pv) : "1" (pv), "q" (nv), "0" (cv));
    return __res;
}

typedef void * pvoid;

//function: set *pv to nv
//return: the initial value of *pv
/// 把nv原子地赋值给*pv
static __inline__ pvoid atomic_exchange_pointer(volatile pvoid * pv, const pvoid nv)
{
#ifdef __x86_64__
    return (pvoid) atomic_exchange((uint64_t *) pv, (uint64_t) nv);
#else
    return (pvoid) atomic_exchange((uint32_t *) pv, (uint32_t) nv);
#endif
}
//function: compare *pv to cv, if equal, set *pv to nv, otherwise do nothing.
//return: the initial value of *pv
/// 比较cv和*pv，如果两者相等则把nv赋值给*pv，并且返回*pv原有数值
/// 否则返回*pv原有数值，不做赋值操作
static __inline__ pvoid atomic_compare_exchange_pointer(volatile pvoid * pv, const pvoid nv, const pvoid cv)
{
#ifdef __x86_64__
    return (pvoid) atomic_compare_exchange((uint64_t *) pv, (uint64_t) nv, (uint64_t) cv);
#else
    return (pvoid) atomic_compare_exchange((uint32_t *) pv, (uint32_t) nv, (uint32_t)cv);
#endif
}

#undef LOCK_PREFIX

/*
 * MFS Atomic Class hold uint64_t values
 */
class MfsAtomic
{
public:
    MfsAtomic()
            : m_value(0)
    {
    }

    explicit MfsAtomic(uint64_t value)
            : m_value(value)
    {
    }

    ~MfsAtomic()
    {
    }

    MfsAtomic(const MfsAtomic& rhs)
    {
        m_value = rhs.m_value;
    }

public:
    inline MfsAtomic& operator=(const MfsAtomic& rhs)
    {
        if (this != &rhs)
            set(rhs.m_value);

        return *this;
    }

    inline uint64_t operator++()
    {
#ifdef __GNUC__
        return __sync_fetch_and_add(&m_value, 1L);
#else
        return atomic_add(&m_value, 1L);
#endif
    }

    inline uint64_t operator--()
    {
#ifdef __GNUC__
        return __sync_fetch_and_add(&m_value, -1L);
#else
        return atomic_dec(&m_value);
#endif
    }

    //
    // Note: 在return的时候，原子性已经被破坏了， 返回的并一定是本次操作之后的值
    //
    inline MfsAtomic& operator+=(uint64_t value)
    {
#ifdef __GNUC__
        __sync_fetch_and_add(&m_value, value);
#else
        atomic_add(&m_value, value);
#endif
        return *this;
    }

    /**
     * 原子的赋值新value，返回原始value
     */
    inline uint64_t set(uint64_t value)
    {
#ifdef __GNUC__
        uint64_t old_value = 0;
        do
        {
            old_value = m_value;
        } while (!__sync_bool_compare_and_swap(&m_value, old_value, value));
        return old_value;
#else
        return atomic_exchange(&m_value, value);
#endif
    }

    inline operator uint64_t()
    {
        return get_value();
    }

    inline uint64_t get_value()
    {
#ifdef __GNUC__
        return __sync_fetch_and_add(&m_value, 0L);
#else
        return atomic_add(&m_value, 0L);
#endif
    }

    inline uint64_t get_value_unsafe() const
    {
        return m_value;
    }

    bool compare_and_set(uint64_t old_value, uint64_t new_value)
    {
#ifdef __GNUC__
        return __sync_bool_compare_and_swap(&m_value, old_value, new_value);
#else
        uint64_t v = atomic_compare_exchange(&m_value, old_value, new_value);
        return v == new_value;
#endif
    }

private:
    mutable volatile uint64_t m_value;
};

#else // #if defined(__i386__) || defined(__x86_64__)
#error "must compiled on i386 or x86_64"

#endif //
}
}
}
}
#endif // _METRICS__ATOMIC_H_
