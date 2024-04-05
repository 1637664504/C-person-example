void test_3(int* p)
{
    *p = 0xff;
}

void test_2(int* p)
{
    test_3(p);
}

void test_1(int* p)
{
    test_2(p);
}

int main(void)
{
    int* p = (int*)0x12345678;
    test_1(p);

    return 0;
}
