#include <unity.h>
#include <Math.h>
#include <Filter.h>

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_math_map()
{
    TEST_ASSERT_FLOAT_WITHIN(1.f,     0.f, Espfc::Math::map(   0.0f, -100.0f, 100.0f, -1000.0f, 1000.0f));
    TEST_ASSERT_FLOAT_WITHIN(1.f,  1000.f, Espfc::Math::map( 100.0f, -100.0f, 100.0f, -1000.0f, 1000.0f));
    TEST_ASSERT_FLOAT_WITHIN(1.f, -1000.f, Espfc::Math::map(-100.0f, -100.0f, 100.0f, -1000.0f, 1000.0f));
    TEST_ASSERT_FLOAT_WITHIN(1.f,   200.f, Espfc::Math::map(  20.0f, -100.0f, 100.0f, -1000.0f, 1000.0f));

    TEST_ASSERT_FLOAT_WITHIN(.001f,  0.f, Espfc::Math::map(   0.0f, -100.0f, 100.0f, -1.0f, 1.0f));
    TEST_ASSERT_FLOAT_WITHIN(.001f,  1.f, Espfc::Math::map( 100.0f, -100.0f, 100.0f, -1.0f, 1.0f));
    TEST_ASSERT_FLOAT_WITHIN(.001f, -1.f, Espfc::Math::map(-100.0f, -100.0f, 100.0f, -1.0f, 1.0f));
}

void test_math_map3()
{
    TEST_ASSERT_FLOAT_WITHIN(1.f,    0.f, Espfc::Math::map3(  0.0f, -100.0f, 0.0f, 100.0f, -1000.0f, 0.0f, 1000.0f));
    TEST_ASSERT_FLOAT_WITHIN(1.f,  500.f, Espfc::Math::map3( 50.0f, -100.0f, 0.0f, 100.0f, -1000.0f, 0.0f, 1000.0f));
    TEST_ASSERT_FLOAT_WITHIN(1.f, -500.f, Espfc::Math::map3(-50.0f, -100.0f, 0.0f, 100.0f, -1000.0f, 0.0f, 1000.0f));
}

void test_math_deadband()
{
    TEST_ASSERT_EQUAL_INT32( 0, Espfc::Math::deadband(  0, 10));
    TEST_ASSERT_EQUAL_INT32( 0, Espfc::Math::deadband( 10, 10));
    TEST_ASSERT_EQUAL_INT32( 1, Espfc::Math::deadband( 11, 10));
    TEST_ASSERT_EQUAL_INT32(-1, Espfc::Math::deadband(-11, 10));
    TEST_ASSERT_EQUAL_INT32( 0, Espfc::Math::deadband( -5, 10));
    TEST_ASSERT_EQUAL_INT32(10, Espfc::Math::deadband( 20, 10));
}

void assert_filter_off(Espfc::Filter& filter)
{
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, filter.update(0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.1f, filter.update(0.1f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5f, filter.update(0.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.5f, filter.update(1.5f));
}

void test_filter_default()
{
    Espfc::Filter filter;
    assert_filter_off(filter);
}

void test_filter_none()
{
    Espfc::Filter filter;
    const Espfc::FilterConfig config(Espfc::FILTER_NONE, 0);
    filter.begin(config, 100);
    assert_filter_off(filter);
}

void test_filter_pt1_off()
{
    Espfc::Filter filter;
    const Espfc::FilterConfig config(Espfc::FILTER_PT1, 0);
    filter.begin(config, 100);
    assert_filter_off(filter);
}

void test_filter_pt1_50_100()
{
    Espfc::Filter filter;
    const Espfc::FilterConfig config(Espfc::FILTER_PT1, 50);
    filter.begin(config, 100);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.000f, filter.update(0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.076f, filter.update(0.1f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.397f, filter.update(0.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.234f, filter.update(1.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.436f, filter.update(1.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.484f, filter.update(1.5f));
}

void test_filter_biquad_off()
{
    Espfc::Filter filter;
    const Espfc::FilterConfig config(Espfc::FILTER_BIQUAD, 0);
    filter.begin(config, 100);
    assert_filter_off(filter);
    TEST_ASSERT_TRUE(false);
}

void test_filter_biquad_20_100()
{
    Espfc::Filter filter;
    const Espfc::FilterConfig config(Espfc::FILTER_BIQUAD, 20);
    filter.begin(config, 100);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.000f, filter.update(0.0f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.020f, filter.update(0.1f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.152f, filter.update(0.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.589f, filter.update(1.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.220f, filter.update(1.5f));
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.575f, filter.update(1.5f));
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_math_map);
    RUN_TEST(test_math_map3);
    RUN_TEST(test_math_deadband);
    RUN_TEST(test_filter_default);
    RUN_TEST(test_filter_none);
    RUN_TEST(test_filter_pt1_off);
    RUN_TEST(test_filter_pt1_50_100);
    RUN_TEST(test_filter_biquad_off);
    RUN_TEST(test_filter_biquad_20_100);
    UNITY_END();

    return 0;
}