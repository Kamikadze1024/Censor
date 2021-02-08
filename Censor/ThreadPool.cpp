#include "ThreadPool.hpp"

namespace Concurrency {

ThreadPool::ThreadPool() {
    //с самого начала, разрешаю потоку работать
    m_thdFlag.store(true);

    //оптимальное количество потоков
    int thdCntr = std::thread::hardware_concurrency();

    try {
        //создаю потоки и добавляю в пул
        for(int i = 0; i < thdCntr; i++) {
            m_threads.emplace_back(&ThreadPool::threadMethod, this);
        }
    } catch(...) {
        m_thdFlag.store(false);
        throw;
    }
}

ThreadPool::~ThreadPool() {
    m_thdFlag.store(false);
}

//"рабочий" метод потока
void ThreadPool::threadMethod() {

}

}
