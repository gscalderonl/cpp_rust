#include <benchmark/benchmark.h>
#include <spdlog/spdlog.h>
#include <vector>
#include <string>
#include "animal.hpp"
#include "person.hpp"

static void BM_log_string_using_spdlog()
{
    std::string message = "This is a test message";

    for (auto _ : state)
    {
        spdlog::info(message);
    }
}

static void BM_log_int_using_spdlog()
{
    int level = 1;

    for (auto _ : state)
    {
        spdlog::info(level);
    }
}

static void BM_log_vector_using_spdlog()
{
    std::vector<std::string> attributes = {"A1", "A2", "A3"};

    for (auto _ : state)
    {
        spdlog::info(attributes);
    }
}

static void BM_log_struct_using_spdlog()
{
    Person p1;
    p1.name = "John";
    p1.age = 30;

    for(auto _ : state)
    {
        spdlog::info(p1);
    }
}

static void BM_log_class_using_spdlog()
{
    Animal dog(42);

    for(auto _ : state)
    {
        spdlog(dog);
    }
}

BENCHMARK(BM_log_string_using_spdlog);
BENCHMARK(BM_log_int_using_spdlog);
BENCHMARK(BM_log_vector_using_spdlog);
BENCHMARK(BM_log_struct_using_spdlog);
BENCHMARK(BM_log_class_using_spdlog);


int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
}