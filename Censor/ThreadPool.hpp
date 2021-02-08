/*
 * Простой пул потоков.
 * Кашицын Денис, 2021
 * <kamikadze1024@yandex.ru>
 */
#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <thread>
#include <vector>
#include <atomic>

namespace Concurrency {

class ThreadPool final {
private:
    //вектор потоков
    std::vector<std::thread> m_threads;

    //переменная работы потока
    std::atomic<bool>        m_thdFlag;

    //"рабочий" метод потока
    void threadMethod();

public:
    ThreadPool();
    ~ThreadPool();
};

}

#endif // THREADPOOL_HPP
