Requires the facebook PHP client library.

There is a weird issue with the client library that sets cookies in the current
path rather than at the root, so I changed all the setcookie() declarations to
use "/" as the path argument.