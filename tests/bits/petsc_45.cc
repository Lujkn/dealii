//----------------------------  petsc_45.cc  ---------------------------
//    $Id$
//    Version: $Name$ 
//
//    Copyright (C) 2004 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------  petsc_45.cc  ---------------------------


// check petsc_wrapper::Vector::scale

#include "../tests.h"
#include <lac/petsc_vector.h>    
#include <fstream>
#include <iostream>
#include <vector>


void test (petsc_wrappers::Vector &v,
           petsc_wrappers::Vector &w)
{
  for (unsigned int i=0; i<v.size(); ++i)
    {
      v(i) = i;
      w(i) = i+1.;
    }
  
  v.compress ();
  w.compress ();

  v.scale (w);

                                   // make sure we get the expected result
  for (unsigned int i=0; i<v.size(); ++i)
    {
      Assert (w(i) == i+1., ExcInternalError());
      Assert (v(i) == i*(i+1.), ExcInternalError());
    }

  deallog << "OK" << std::endl;
}



int main (int argc,char **argv) 
{
  std::ofstream logfile("petsc_45.output");
  deallog.attach(logfile);
  deallog.depth_console(0);

  try
    {
      PetscInitialize(&argc,&argv,0,0);
      {
        petsc_wrappers::Vector v (100);
        petsc_wrappers::Vector w (100);
        test (v,w);
      }
      PetscFinalize();
    }
  catch (std::exception &exc)
    {
      std::cerr << std::endl << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      std::cerr << "Exception on processing: " << std::endl
		<< exc.what() << std::endl
		<< "Aborting!" << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      
      return 1;
    }
  catch (...) 
    {
      std::cerr << std::endl << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      std::cerr << "Unknown exception!" << std::endl
		<< "Aborting!" << std::endl
		<< "----------------------------------------------------"
		<< std::endl;
      return 1;
    };
}
