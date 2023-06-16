#include "spdlog/spdlog.h"
#include "spdlog/sinks/null_sink.h"
#include "benchmark/benchmark.h"
#include "person.hpp"
#include "animal.hpp"
#include <vector>
#include <string>

std::string to_string(const std::vector<std::string>& v)
{
    std::string s = "Vector: [";
    for (const auto& item : v) {
        s += item + ", ";
    }
    s = s.substr(0, s.length() - 2); // Remove the trailing comma
    s += "]";
    return s;
}

static void BM_log_string_using_spdlog(benchmark::State& state)
{
    std::string message = "This is a test message";
    for(auto _ : state)
    {
        spdlog::info(message);
    }
}

static void BM_log_int_using_spdlog(benchmark::State& state)
{
    int level = 1;

    for (auto _ : state)
    {
        spdlog::info(level);
    }
}

static void BM_log_vector_using_spdlog(benchmark::State& state)
{
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};

    for (auto _ : state)
    {
        spdlog::info("{}", to_string(names));
    }
}

static void BM_log_struct_using_spdlog(benchmark::State& state)
{
    Person p1;
    p1.name = "John";
    p1.age = 30;

    for(auto _ : state)
    {
        spdlog::info("Received persons: {} who is {} years old", p1.name, p1.age);
    }
}

static void BM_log_class_using_spdlog(benchmark::State& state)
{
    Animal dog(42);

    for(auto _ : state)
    {
        spdlog::info("{}", dog.get_age());
    }
}

BENCHMARK(BM_log_string_using_spdlog);
BENCHMARK(BM_log_int_using_spdlog);
BENCHMARK(BM_log_vector_using_spdlog);
BENCHMARK(BM_log_struct_using_spdlog);
BENCHMARK(BM_log_class_using_spdlog);

int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
    auto logger = std::make_shared<spdlog::logger>("null_logger", null_sink);
    spdlog::set_default_logger(logger);
    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
}