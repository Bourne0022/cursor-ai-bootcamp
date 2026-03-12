// singleton.cpp
// 线程安全懒加载单例示例（C++11+）
#include <iostream>
#include <mutex>
#include <string>

class Config {
public:
    // 获取唯一实例（线程安全，C++11 保证局部静态初始化只执行一次）
    static Config& instance() {
        static Config inst;
        return inst;
    }

    void setValue(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(mu_);
        data_ = "Key=" + key + ", Value=" + value;
    }

    std::string getValue() const {
        std::lock_guard<std::mutex> lock(mu_);
        return data_;
    }

private:
    Config() = default;
    ~Config() = default;

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(Config&&) = delete;

    mutable std::mutex mu_;
    std::string data_;
};

int main() {
    // 示例使用
    auto& cfg = Config::instance();
    cfg.setValue("theme", "light");
    std::cout << cfg.getValue() << '\n';

    // 多处获取仍是同一实例
    Config::instance().setValue("lang", "zh-CN");
    std::cout << Config::instance().getValue() << '\n';
    return 0;
}
