cmake_minimum_required(VERSION 3.31)
project(Labs)

set(CMAKE_CXX_STANDARD 23)

add_executable(Labs main.cpp Student.cpp
        Subjects.h
        Subjects.cpp
        Helper.h
        Helper.cpp
        Functional.cpp
        Functional.h
        Employee.cpp
        Employee.h
        SalariedEmployee.cpp
        SalariedEmployee.h
        HourlyEmployee.cpp
        HourlyEmployee.h
        CommissionEmployee.cpp
        CommissionEmployee.h)
