add_executable(StatisticsApp 
            main.cpp
            Receiver.cpp
            Statistics.cpp)

target_link_libraries(StatisticsApp PRIVATE LoggerLib)