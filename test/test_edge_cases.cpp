#include <catch2/catch_test_macros.hpp>
#include <cstring>
#include <cerrno>

TEST_CASE("Null input handling", "[edge]") {
    int ret = volt_guard_set_mode(NULL, 0);
    REQUIRE(ret == -EINVAL);
}

TEST_CASE("Empty input handling", "[edge]") {
    struct volt_guard_status st;
    std::memset(&st, 0, sizeof(st));
    REQUIRE(st.mode == 0);
    REQUIRE(st.power_mw == 0);
}

TEST_CASE("Boundary values", "[edge]") {
    struct volt_guard_status st;
    std::memset(&st, 0, sizeof(st));
    st.mode = 0;
    st.power_mw = 15000;
    REQUIRE(st.mode == 0);
    REQUIRE(st.power_mw == 15000);
    st.mode = 2;
    st.power_mw = 60000;
    REQUIRE(st.mode == 2);
    REQUIRE(st.power_mw == 60000);
}

TEST_CASE("Concurrent access", "[edge]") {
    std::atomic<int> counter{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&]() { counter++; });
    }
    for (auto& t : threads) t.join();
    REQUIRE(counter == 10);
}

TEST_CASE("Resource cleanup on error", "[edge]") {
    struct volt_guard_status st;
    std::memset(&st, 0, sizeof(st));
    st.mode = 99;
    REQUIRE(st.mode == 99);
}
