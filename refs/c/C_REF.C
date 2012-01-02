//////////////////////////////////////////////////////////////////////////
int _chmod( 
   const char *filename,
   int pmode 
);
pmode:
_S_IWRITE
Writing permitted.

_S_IREAD
Reading permitted.

_S_IREAD | _S_IWRITE

//////////////////////////////////////////////////////////////////////////
errno:
#include <errno.h>
#define E2BIG [argument list too long]
#define EACCES [permission denied]
#define EADDRINUSE [address in use]
#define EADDRNOTAVAIL [address not available]
#define EAFNOSUPPORT [address family not supported]
#define EAGAIN [resource unavailable try again]
#define EALREADY [connection already in progress]
#define EBADF [bad file descriptor]
#define EBADMSG [bad message]
#define EBUSY [device or resource busy]
#define ECANCELED [operation canceled]
#define ECHILD [no child process]
#define ECONNABORTED [connection aborted]
#define ECONNREFUSED [connection refused]
#define ECONNRESET [connection reset]
#define EDEADLK [resource deadlock would occur]
#define EDESTADDRREQ [destination address required]
#define EDOM [argument out of domain]
#define EEXIST [file exists]
#define EFAULT [bad address]
#define EFBIG [file too large]
#define EHOSTUNREACH [host unreachable]
#define EIDRM [identifier removed]
#define EILSEQ [illegal byte sequence]
#define EINPROGRESS [operation in progress]
#define EINTR [interrupted]
#define EINVAL [invalid argument]
#define EIO [io error]
#define EISCONN [already connected]
#define EISDIR [is a directory]
#define ELOOP [too many synbolic link levels]
#define EMFILE [too many files open]
#define EMLINK [too many links]
#define EMSGSIZE [message size]
#define ENAMETOOLONG [filename too long]
#define ENETDOWN [network down]
#define ENETRESET [network reset]
#define ENETUNREACH [network unreachable]
#define ENFILE [too many files open in system]
#define ENOBUFS [no buffer space]
#define ENODATA [no message available]
#define ENODEV [no such device]
#define ENOENT [no such file or directory]
#define ENOEXEC [executable format error]
#define ENOLCK [no lock available]
#define ENOLINK [no link]
#define ENOMEM [not enough memory]
#define ENOMSG [no message]
#define ENOPROTOOPT [no protocol option]
#define ENOSPC [no space on device]
#define ENOSR [no stream resources]
#define ENOSTR [not a stream]
#define ENOSYS [function not supported]
#define ENOTCONN [not connected]
#define ENOTDIR [not a directory]
#define ENOTEMPTY [directory not empty]
#define ENOTRECOVERABLE [state not recoverable]
#define ENOTSOCK [not a socket]
#define ENOTSUP [not supported]
#define ENOTTY [inappropriate io control operation]
#define ENXIO [no such device or address]
#define EOPNOTSUPP [operation not supported]
#define EOTHER [other]
#define EOVERFLOW [value too large]
#define EOWNERDEAD [owner dead]
#define EPERM [operation not permitted]
#define EPIPE [broken pipe]
#define EPROTO [protocol error]
#define EPROTONOSUPPORT [protocol not supported]
#define EPROTOTYPE [wrong protocol type]
#define ERANGE [result out of range]
#define EROFS [read only file system]
#define ESPIPE [invalid seek]
#define ESRCH [no such process]
#define ETIME [stream timeout]
#define ETIMEDOUT [timed out]
#define ETXTBSY [text file busy]
#define EWOULDBLOCK [operation would block]
#define EXDEV [cross device link]

//////////////////////////////////////////////////////////////////////////
system()
http://msdn.microsoft.com/en-US/library/277bwbdz(v=VS.80).aspx

