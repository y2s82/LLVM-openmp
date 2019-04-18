// RUN: %gdb-compile-and-run

#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <pthread.h>
#include "../ompt_plugin.h"

void f(int i)
{
  if ( i<=0 )
  {
    ompd_tool_test(0);
  }
  else
  {
    printf("f(%i) start task 1\n", i);
    #pragma omp task
      f(i-1);
    printf("f(%i) start task 2\n", i);
    #pragma omp task
      f(i-1);
    printf("f(%i) start task 3\n", i);
    #pragma omp task
      f(i-1);
    #pragma omp taskwait
  }
}

int main()
{
  printf("Application: Process %d started.\n", getpid());
  omp_set_num_threads(8);
  omp_set_nested(1); // 1:enables nested parall.; 0:disables nested parall.

#pragma omp parallel sections
{
  f(4);
}

  return 0;
}

// CHECK-NOT: "Error"
// CHECK-NOT: "The program is not being run."
