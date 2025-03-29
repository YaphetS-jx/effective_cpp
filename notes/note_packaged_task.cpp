#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
 
// unique function to avoid disambiguating the std::pow overload set
int f(int x, int y) { return std::pow(x, y); }
 
void task_lambda()
{
    std::packaged_task<int(int, int)> task([](int a, int b)
    {
        return std::pow(a, b); 
    });
    std::future<int> result = task.get_future();
 
    task(2, 9);
 
    std::cout << "task_lambda:\t" << result.get() << '\n';
}
 
void task_bind()
{
    // bind the function f to the arguments 2 and 11
    std::packaged_task<int()> task(std::bind(f, 2, 11));
    std::future<int> result = task.get_future();
    
    // no need to add input 2 and 11, because the function f is already bound to the arguments
    task();
 
    std::cout << "task_bind:\t" << result.get() << '\n';
}
 
void task_thread()
{
    std::packaged_task<int(int, int)> task(f);
    std::future<int> result = task.get_future();
    // move task to be a rvalue instead of copy it 
    // task is no longer valid after this point
    std::thread task_td(std::move(task), 2, 10);
    task_td.join();
 
    std::cout << "task_thread:\t" << result.get() << '\n';
}
 
int main()
{
    task_lambda();
    task_bind();
    task_thread();
}