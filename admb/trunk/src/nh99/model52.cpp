/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#if defined(USE_LAPLACE)
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>



  void random_effects_number::set_only_random_effects_active(void)
  {
    //phase_start=1;
    phase_start=phase_save;
  }


  void random_effects_vector::set_only_random_effects_active(void)
  {
    //phase_start=1;
    phase_start=phase_save;
  }

  void random_effects_matrix::set_only_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_bounded_number::set_only_random_effects_active(void)
  {
    //phase_start=1;
    phase_start=phase_save;
  }


  void random_effects_bounded_vector::set_only_random_effects_active(void)
  {
    //phase_start=1;
    phase_start=phase_save;
  }

  void random_effects_bounded_matrix::set_only_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_number::set_only_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_vector::set_only_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_matrix::set_only_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_bounded_number::set_only_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_bounded_vector::set_only_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_bounded_matrix::set_only_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_number::set_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_vector::set_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_matrix::set_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_bounded_number::set_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_bounded_vector::set_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_bounded_matrix::set_random_effects_active(void)
  {
    phase_start=phase_save;
  }

  void random_effects_number::set_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_vector::set_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_matrix::set_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_bounded_number::set_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_bounded_vector::set_random_effects_inactive(void)
  {
    phase_start=-1;
  }

  void random_effects_bounded_matrix::set_random_effects_inactive(void)
  {
    phase_start=-1;
  }

#endif
