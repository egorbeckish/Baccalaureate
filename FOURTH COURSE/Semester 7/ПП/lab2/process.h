#pragma once
#include "mpi.h"
#include "init_process.h"

class Process : public Init_Process
{
    protected:
        int process_ID;
        enum PIDs
        {
            INIT
        };

    public:
        Process(int argc, char* argv[], MPI_Comm comm = MPI_COMM_WORLD) : Init_Process(argc, argv, comm) {
            MPI_Comm_rank(comm, &process_ID);
        }

        int get_process_ID() const {
            return process_ID;
        }

        void printInfo(std::string accompanying_message = "", std::ostream& out = std::cout) {
            out << "\n"
                << process_ID << ": " << accompanying_message;
            fflush(NULL);
        }

        void send(void* buffer, int to_process_ID, MPI_Datatype type = MPI_INT, int count = 1, int tag = 1) {
            MPI_Send(buffer, count, type, to_process_ID, tag, _comm);
        }

        MPI_Status recv(void* buffer, int from_process_ID, MPI_Datatype type = MPI_INT, int count = 1, int tag = 1) {
            MPI_Status status;
            MPI_Recv(buffer, count, type, from_process_ID, tag, _comm, &status);
            return status;
        }

        void bcast(void* buffer, MPI_Datatype type = MPI_INT, int count = 1, int root = Process::INIT) {
            MPI_Bcast(buffer, count, type, root, _comm);
        }

        void reduce(void* send_buffer, void* recv_buffer, MPI_Datatype type = MPI_INT, int root = Process::INIT, MPI_Op op = MPI_SUM, int count = 1) {
            MPI_Reduce(send_buffer, recv_buffer, count, type, op, root, _comm);
        }

        void pack(void* in_buffer, int count, void* out_buffer, int count_buffer, MPI_Datatype type = MPI_INT, int* position = NULL) {
            MPI_Pack(in_buffer, count, type, out_buffer, count_buffer, position, _comm);
        }

        void unpack(void* in_buffer, int insize, void* out_buffer, int* position, MPI_Datatype type = MPI_INT, int count = 1) {
            MPI_Unpack(in_buffer, insize, position, out_buffer, count, type, _comm);
        }
};