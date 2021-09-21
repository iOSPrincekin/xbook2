#include <xbook/debug.h>
//#define interrupt_test
void test_kernel()
{
#ifdef interrupt_test
	int* x = 0xcfffffff;
	int b = (int)*x;
	dbgprint("b--::%d\n",b);
#endif
}
