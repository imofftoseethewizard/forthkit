/* SWAP ( n1 n2 -- n2 n1 )

   Exchange the top two stack values.
 */
#define _swap() do { register cell tmp = *sp; *sp = *(sp+1), *(sp+1) = tmp; } while(0)
