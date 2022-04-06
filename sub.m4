include(`preamble.m4')
define(`primitive', `divert(1)auto void pr_$1(void);
divert(2)void pr_$1(void)')dnl
