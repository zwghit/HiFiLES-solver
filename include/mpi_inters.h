/*!
 * \file mpi_inters.h
 * \brief _____________________________
 * \author - Original code: SD++ developed by Patrice Castonguay, Antony Jameson,
 *                          Peter Vincent, David Williams (alphabetical by surname).
 *         - Current development: Aerospace Computing Laboratory (ACL) directed
 *                                by Prof. Jameson. (Aero/Astro Dept. Stanford University).
 * \version 1.0.0
 *
 * HiFiLES (High Fidelity Large Eddy Simulation).
 * Copyright (C) 2013 Aerospace Computing Laboratory.
 */

#pragma once

#include "inters.h"
#include "array.h"
#include "solution.h"

#ifdef _MPI
#include "mpi.h"
#endif

struct solution; // forwards declaration

class mpi_inters: public inters
{
public:

  // #### constructors ####

  // default constructor

  mpi_inters();

  // default destructor

  ~mpi_inters();

  // #### methods ####

  /*! setup mpi_inters */
  void setup(int in_n_inters, int in_inter_type);

  void set_nproc(int in_nproc, int in_rank);

  void set_nout_proc(int in_nout,int in_p);

  void set_mpi_requests(int in_number_of_request);

  void send_solution();

  void receive_solution();

  void send_corrected_gradient();

  void receive_corrected_gradient();

  void send_sgsf_fpts();

  void receive_sgsf_fpts();

  void set_mpi(int in_inter, int in_ele_type_l, int in_ele_l, int in_local_inter_l, int rot_tag, struct solution* FlowSol);

  void calculate_common_invFlux(void);
  void calculate_common_viscFlux(void);

  /*! move all from cpu to gpu */
  void mv_all_cpu_gpu(void);

protected:

  // #### members ####

  array<double*> disu_fpts_r;
  array<double*> grad_disu_fpts_r;

  int nproc;
  int rank;
  int Nmess;

  array<double> out_buffer_disu, in_buffer_disu;
  array<int> Nout_proc;

  // Viscous
  array<double> out_buffer_grad_disu, in_buffer_grad_disu;

  // LES
  array<double> out_buffer_sgsf, in_buffer_sgsf;

#ifdef _MPI
  MPI_Request *mpi_out_requests;
  MPI_Request *mpi_in_requests;
  MPI_Request *mpi_out_requests_grad;
  MPI_Request *mpi_in_requests_grad;
  MPI_Request *mpi_out_requests_sgsf;
  MPI_Request *mpi_in_requests_sgsf;

  MPI_Status *mpi_instatus;
  MPI_Status *mpi_outstatus;
#endif

};
