#pragma once
#include <iostream>
#include "mpi.h"


class Init_Process {
    protected:
        MPI_Comm _comm;
        int numprocs;
        char processor_name[MPI_MAX_PROCESSOR_NAME];
        int namelen;
        //int rank;

    protected:
        Init_Process(int argc, char* argv[], MPI_Comm comm = MPI_COMM_WORLD)
        {
            MPI_Init(&argc, &argv);

            _comm = comm;
            MPI_Comm_size(_comm, &numprocs);
            //MPI_Comm_rank(_comm, &rank);
            MPI_Get_processor_name(processor_name, &namelen);
        }

        ~Init_Process() {
            MPI_Finalize();
        }

    public:
        virtual void printInfo(std::string accompanying_message = "", std::ostream& out = std::cout)
        {
            out << "\nИмя процесса: " << processor_name
                << "\nНомер процесса: " << numprocs
                << "\n" << accompanying_message;
            fflush(NULL);
        }
};