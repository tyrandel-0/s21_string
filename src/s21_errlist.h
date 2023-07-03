#ifndef S21_ERRLIST
#define S21_ERRLIST

#ifdef __APPLE__
#define ERR_MAX 106
#define UNKNOWN_ERROR "Unknown error: "
#define ERRORS                                                                \
  char error_list[][50] = {"Undefined error: 0",                              \
                           "Operation not permitted",                         \
                           "No such file or directory",                       \
                           "No such process",                                 \
                           "Interrupted system call",                         \
                           "Input/output error",                              \
                           "Device not configured",                           \
                           "Argument list too long",                          \
                           "Exec format error",                               \
                           "Bad file descriptor",                             \
                           "No child processes",                              \
                           "Resource deadlock avoided",                       \
                           "Cannot allocate memory",                          \
                           "Permission denied",                               \
                           "Bad address",                                     \
                           "Block device required",                           \
                           "Resource busy",                                   \
                           "File exists",                                     \
                           "Cross-device link",                               \
                           "Operation not supported by device",               \
                           "Not a directory",                                 \
                           "Is a directory",                                  \
                           "Invalid argument",                                \
                           "Too many open files in system",                   \
                           "Too many open files",                             \
                           "Inappropriate ioctl for device",                  \
                           "Text file busy",                                  \
                           "File too large",                                  \
                           "No space left on device",                         \
                           "Illegal seek",                                    \
                           "Read-only file system",                           \
                           "Too many links",                                  \
                           "Broken pipe",                                     \
                           "Numerical argument out of domain",                \
                           "Result too large",                                \
                           "Resource temporarily unavailable",                \
                           "Operation now in progress",                       \
                           "Operation already in progress",                   \
                           "Socket operation on non-socket",                  \
                           "Destination address required",                    \
                           "Message too long",                                \
                           "Protocol wrong type for socket",                  \
                           "Protocol not available",                          \
                           "Protocol not supported",                          \
                           "Socket type not supported",                       \
                           "Operation not supported",                         \
                           "Protocol family not supported",                   \
                           "Address family not supported by protocol family", \
                           "Address already in use",                          \
                           "Can't assign requested address",                  \
                           "Network is down",                                 \
                           "Network is unreachable",                          \
                           "Network dropped connection on reset",             \
                           "Software caused connection abort",                \
                           "Connection reset by peer",                        \
                           "No buffer space available",                       \
                           "Socket is already connected",                     \
                           "Socket is not connected",                         \
                           "Can't send after socket shutdown",                \
                           "Too many references: can't splice",               \
                           "Operation timed out",                             \
                           "Connection refused",                              \
                           "Too many levels of symbolic links",               \
                           "File name too long",                              \
                           "Host is down",                                    \
                           "No route to host",                                \
                           "Directory not empty",                             \
                           "Too many processes",                              \
                           "Too many users",                                  \
                           "Disc quota exceeded",                             \
                           "Stale NFS file handle",                           \
                           "Too many levels of remote in path",               \
                           "RPC struct is bad",                               \
                           "RPC version wrong",                               \
                           "RPC prog. not avail",                             \
                           "Program version wrong",                           \
                           "Bad procedure for program",                       \
                           "No locks available",                              \
                           "Function not implemented",                        \
                           "Inappropriate file type or format",               \
                           "Authentication error",                            \
                           "Need authenticator",                              \
                           "Device power is off",                             \
                           "Device error",                                    \
                           "Value too large to be stored in data type",       \
                           "Bad executable (or shared library)",              \
                           "Bad CPU type in executable",                      \
                           "Shared library version mismatch",                 \
                           "Malformed Mach-o file",                           \
                           "Operation canceled",                              \
                           "Identifier removed",                              \
                           "No message of desired type",                      \
                           "Illegal byte sequence",                           \
                           "Attribute not found",                             \
                           "Bad message",                                     \
                           "EMULTIHOP (Reserved)",                            \
                           "No message available on STREAM",                  \
                           "ENOLINK (Reserved)",                              \
                           "No STREAM resources",                             \
                           "Not a STREAM",                                    \
                           "Protocol error",                                  \
                           "STREAM ioctl timeout",                            \
                           "Operation not supported on socket",               \
                           "Policy not found",                                \
                           "State not recoverable",                           \
                           "Previous owner died",                             \
                           "Interface output queue is full"}

#elif __linux__

#define ERR_MAX 40
#define UNKNOWN_ERROR "Unknown error "
#define ERRORS                                                 \
  char error_list[][50] = {"Success",                          \
                           "Operation not permitted",          \
                           "No such file or directory",        \
                           "No such process",                  \
                           "Interrupted system call",          \
                           "Input/output error",               \
                           "No such device or address",        \
                           "Argument list too long",           \
                           "Exec format error",                \
                           "Bad file descriptor",              \
                           "No child processes",               \
                           "Resource temporarily unavailable", \
                           "Cannot allocate memory",           \
                           "Permission denied",                \
                           "Bad address",                      \
                           "Block device required",            \
                           "Device or resource busy",          \
                           "File exists",                      \
                           "Invalid cross-device link",        \
                           "No such device",                   \
                           "Not a directory",                  \
                           "Is a directory",                   \
                           "Invalid argument",                 \
                           "Too many open files in system",    \
                           "Too many open files",              \
                           "Inappropriate ioctl for device",   \
                           "Text file busy",                   \
                           "File too large",                   \
                           "No space left on device",          \
                           "Illegal seek",                     \
                           "Read-only file system",            \
                           "Too many links",                   \
                           "Broken pipe",                      \
                           "Numerical argument out of domain", \
                           "Numerical result out of range",    \
                           "Resource deadlock avoided",        \
                           "File name too long",               \
                           "No locks available",               \
                           "Function not implemented",         \
                           "Directory not empty",              \
                           "Too many levels of symbolic links"}
#endif

#endif