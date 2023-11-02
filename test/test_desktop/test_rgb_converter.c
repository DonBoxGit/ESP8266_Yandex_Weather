#include <unity.h>
#include "rgb_converter.h"

void add_test(void) {
    uint8_t actual = rgb888_to_rgb565(0xFF9C00);
    TEST_ASSERT_EQUAL_INT16(0xfce0, actual);    
}

void setUp(void) {

}

void tearDown(void) {

}

int main (int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(add_test);
    UNITY_END();
    return 0;
}