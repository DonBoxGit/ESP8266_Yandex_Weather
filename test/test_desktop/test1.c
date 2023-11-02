#include <unity.h>

int add(int a, int b) {
    return a + b;
}

void add_test(void) {
    int actuale = add(3, 4);
    TEST_ASSERT_EQUAL_INT16(7, actuale);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(add_test);
    UNITY_END();
    return 0;
}