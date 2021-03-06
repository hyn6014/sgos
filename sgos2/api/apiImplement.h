
//#define __FASTCALL

#ifdef __FASTCALL

static void ______()
{
	__asm__ __volatile__(
		"after_sysenter:\n\t" 
		"popl %%edx;" 
		"popl %%ecx;"
		"popl %%ebx;"
		"popl %%esi"
	::);
}

#define SYSCALL0(id, type,name) \
type Api_##name(void) \
{ \
	__asm__ __volatile__ ( \
		"pushl %%ecx\n\t" \
		"pushl %%edx\n\t" \
		"movl %%esp, %%ebp\n\t" \
		"leal after_sysenter, %%esi\n\t" \
		"sysenter\n\t" \
		: \
		: "a" (id) \
		: "%esp", "%ebp","%esi", "%ebx"); \
}

#define SYSCALL1(id, type,name,atype,a) \
type Api_##name(atype a) \
{ \
	__asm__ __volatile__ ( \
		"pushl %%ecx\n\t" \
		"pushl %%edx\n\t" \
		"movl %%esp, %%ebp\n\t" \
		"leal after_sysenter, %%esi\n\t" \
		"sysenter\n\t" \
		: \
		: "a" (id), "b"(a) \
		: "%esp", "%ebp","%esi"); \
}

#define SYSCALL2(id, type,name,atype,a,btype,b) \
type Api_##name(atype a,btype b) \
{ \
	__asm__ __volatile__ ( \
		"pushl %%ecx\n\t" \
		"pushl %%edx\n\t" \
		"movl %%esp, %%ebp\n\t" \
		"leal after_sysenter, %%esi\n\t" \
		"sysenter\n\t" \
		:\
		: "a" (id), "b"(a), "c"(b) \
		: "%esp", "%ebp","%esi"); \
}

#define SYSCALL3(id, type,name,atype,a,btype,b,ctype,c) \
type Api_##name(atype a,btype b,ctype c) \
{ \
	__asm__ __volatile__ ( \
		"pushl %%ecx\n\t" \
		"pushl %%edx\n\t" \
		"movl %%esp, %%ebp\n\t" \
		"leal after_sysenter, %%esi\n\t" \
		"sysenter\n\t" \
		:\
		: "a" (id), "b"(a), "c"(b), "d"(c) \
		: "%esp", "%ebp","%esi"); \
}

#define SYSCALL4(id, type,name,atype,a,btype,b,ctype,c,dtype,d) \
type Api_##name(atype a,btype b,ctype c, dtype d) \
{ \
	__asm__ __volatile__ ( \
		"pushl %%ecx\n\t" \
		"pushl %%edx\n\t" \
		"movl %%esp, %%ebp\n\t" \
		"leal after_sysenter, %%esi\n\t" \
		"sysenter\n\t" \
		:\
		: "a" (id), "b"(a), "c"(b), "d"(c), "D"(d) \
		: "%esp", "%ebp","%esi"); \
}

#else

#define SYSCALL0(id, type,name) \
type Api_##name(void) \
{ \
	long result; \
	__asm__ __volatile__ ("int $0xA1" \
	: "=a" (result) \
	: "a"(id), "c"(0)  ); \
return (type) result; \
}

#define SYSCALL1(id, type,name,atype,a) \
type Api_##name(atype a) \
{ \
	long result; \
	__asm__ __volatile__ ("int $0xA1" \
	: "=a" (result) \
	: "a"(id), "b"(a)  ); \
	return (type) result; \
}

#define SYSCALL2(id, type,name,atype,a,btype,b) \
type Api_##name(atype a,btype b) \
{ \
	long result; \
	__asm__ __volatile__ ("int $0xA1" \
	: "=a" (result) \
	: "a"(id), "b"(a), "c"(b) ); \
	return (type) result; \
}

#define SYSCALL3(id, type,name,atype,a,btype,b,ctype,c) \
type Api_##name(atype a,btype b,ctype c) \
{ \
	long result; \
	__asm__ __volatile__ ("int $0xA1" \
	: "=a" (result) \
	: "a"(id), "b"(a), "c"(b), "d"(c) ); \
	return (type) result; \
}

#define SYSCALL4(id, type,name,atype,a,btype,b,ctype,c,dtype,d) \
type Api_##name(atype a,btype b,ctype c, dtype d) \
{ \
	long result; \
	__asm__ __volatile__ ("int $0xA1" \
	: "=a" (result) \
	: "a"(id), "b"(a), "c"(b), "d"(c), "D"(d) ); \
	return (type) result; \
}

#endif
