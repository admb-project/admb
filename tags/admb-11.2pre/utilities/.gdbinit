#
#   ADMB gdb utilities version 1.00
#
#  Printing of ADMB structures
#
#  Author - Chris Grandin (chrisgrandin@gmail.com)

printf "Loaded .gdbinit\n"

printf "ADMB debugging enabled.\n"
printf "  Printing of ADMB structures:\n"
printf "  dvariable       - pdv dvariableName\n"
printf "  vector, dvector - pvec vectorName\n"
printf "  ivector         - pivec ivectorName\n"
printf "  dvar_vector     - pdvec dvar_vectorName\n"
printf "  matrix, dmatrix - pmat matrixName\n"
printf "  imatrix         - pimat imatrixName\n"
printf "  dvar_matrix     - pdmat dvar_matrixName\n"
printf "  3d_array        - p3d 3darrayName\n"
printf " For help on commands, type command name without arguments.\n"
set print pretty

define pdv
  if $argc == 0 | $argc > 1
    help pdv
  end
  if $argc == 1
    printf "pdv: dvariable value = %f\n", $arg0->v->x
  end
end

document pdv
  Prints ADMB dvariable contents.
  Syntax: pdv <ADMB dvariable>
  Examples:
  pdv f - Prints value of dvariable f
end

define pvec
  if $argc == 0 | $argc > 2
    help pvec
  end
  if $argc == 1
    set $i = $arg0->index_min
    while $i <= $arg0->index_max
      printf "%f\t", *&$arg0[$i]
      set $i = $i + 1
    end
    printf "\n"
  end
  if $argc == 2
    if $arg0 == 1
      set $i = $arg1->index_min
      while $i <= $arg1->index_max
        printf "%f\n", *&$arg1[$i]
        set $i = $i + 1
      end
    end
    if $arg0 == 2
      printf "pvec: (d)vector '$arg1' dimensions: min = %u, max = %u\n",\
      $arg1->index_min, $arg1->index_max
    end
    if $arg0 != 1 & $arg0 !=2
      help pvec
    end
  end
end

document pvec
  Prints ADMB vector and dvector contents.
  Syntax: pvec <ADMB vector or dvector>
  Examples:
  pvec v   - Prints vector contents in row form
  pvec 1 v - Prints vector contents in column form
  pvec 2 v - Prints vector dimensions
end

define pivec
  if $argc == 0 | $argc > 2
    help pivec
  end
  if $argc == 1
    set $i = $arg0->index_min
    while $i <= $arg0->index_max
      printf "%u\t", $arg0->v[$i]
      set $i = $i + 1
    end
    printf "\n"
  end
  if $argc == 2
    if $arg0 == 1
      set $i = $arg1->index_min
      while $i <= $arg1->index_max
        printf "%u\n", $arg1->v[$i]
        set $i = $i + 1
      end
    end
    if $arg0 == 2
      printf "pivec: ivector '$arg1' dimensions: min = %u, max = %u\n",\
      $arg1->index_min, $arg1->index_max
    end
    if $arg0 != 1 & $arg0 !=2
      help pivec
    end
  end
end

document pivec
  Prints ADMB ivector
  Syntax: pivec <ADMB ivector>
  Examples:
  pivec v   - Prints ivector contents in row form
  pivec 1 v - Prints ivector contents in column form
  pivec 2 v - Prints ivector dimensions
end

define pdvec
  if $argc == 0 | $argc > 2
    help pdvec
  end
  if $argc == 1
    set $i = $arg0->index_min
    while $i <= $arg0->index_max
      printf "%f\t", $arg0->va[$i]
      set $i = $i + 1
    end
    printf "\n"
  end
  if $argc == 2
    if $arg0 == 1
      set $i = $arg1->index_min
      while $i <= $arg1->index_max
        printf "%f\n", $arg1->va[$i]
        set $i = $i + 1
      end
    end
    if $arg0 == 2
      printf "pdvec: dvar_vector '$arg1' dimensions: min = %u, max = %u\n",\
      $arg1->index_min, $arg1->index_max
    end
    if $arg0 != 1 & $arg0 !=2
      help pdvec
    end
  end
end

document pdvec
  Prints ADMB dvar_vector contents.
  Syntax: pdvec <ADMB dvar_vector>
  Examples:
  pdvec v - Prints dvar_vector contents in row form
  pdvec 1 v - Prints dvar_vector contents in column form
  pdvec 2 v - Prints dvar_vector dimensions
end

define pmat
  if $argc == 0 | $argc > 2
    help pmat
  end
  if $argc == 1
    set $row = $arg0->index_min
    while $row <= $arg0->index_max
      pvec $arg0->m[$row]
      set $row = $row + 1
    end
  end
  if $argc == 2
    if $arg0 == 2
        printf "pmat: matrix '$arg1' dimensions (rows,columns): %ux%u,%ux%u\n",\
        $arg1->index_min, $arg1->index_max, $arg1->m[$arg1->index_min]->index_min,\
        $arg1->m[$arg1->index_max]->index_max
    else
      help pmat
    end
  end
end

document pmat
  Prints ADMB matrix and dmatrix contents.
  Syntax: pmat <ADMB matrix or dmatrix>
  Examples:
  pmat m - Prints matrix contents
  pmat 2 - Prints matrix dimensions
end

define pimat
  if $argc == 0 | $argc > 2
    help pimat
  end
  if $argc ==1
    set $row = $arg0->index_min
    while $row <= $arg0->index_max
      set $col = $arg0->m[$row]->index_min
      while $col <= $arg0->m[$row]->index_max
        printf  "%u\t", $arg0->m[$row]->v[$col]
        set $col = $col + 1
      end
      set $row = $row + 1
      printf "\n"
    end
  end
  if $argc == 2
    if $arg0 == 2
        printf "pimat: matrix '$arg1' dimensions (rows,columns): %ux%u,%ux%u\n",\
        $arg1->index_min, $arg1->index_max, $arg1->m[1]->index_min,\
        $arg1->m[1]->index_max
    else
      help pimat
    end
  end
end

document pimat
  Prints ADMB imatrix
  Syntax: pimat <ADMB imatrix>
  Examples:
  pimat m - Prints imatrix contents
  pimat 2 - Prints imatrix dimensions
end

define pdmat
  if $argc == 0 | $argc > 2
    help pdmat
  end
  if $argc ==1
    set $row = $arg0->index_min
    while $row <= $arg0->index_max
      set $col = $arg0->m[$row]->index_min
      while $col <= $arg0->m[$row]->index_max
        printf  "%f\t", $arg0->m[$row]->va[$col]
        set $col = $col + 1
      end
      set $row = $row + 1
      printf "\n"
    end
  end
  if $argc == 2
    if $arg0 == 2
        printf "pdmat: matrix '$arg1' dimensions (rows,columns): %ux%u,%ux%u\n",\
        $arg1->index_min, $arg1->index_max, $arg1->m[$arg1->index_min]->index_min,\
        $arg1->m[$arg1->index_max]->index_max
    else
      help pdmat
    end
  end
end

document pdmat
  Prints ADMB dvar_matrix contents
  Syntax: pdmat <ADMB matrix>
  Examples:
  pdmat m - Prints dvar_matrix contents
  pdmat 2 m - Prints dvar_matrix dimensions
end

define p3d
  if $argc == 0 | $argc > 2
    help p3d
  end
  if $argc == 1
    set $curr = $arg0->shape->slice_min
    set $max = $arg0->shape->slice_max
    while $curr <= $max
      printf "p3d: Matrix at 3d index %u:\n",$curr
      pmat $arg0->t[$curr]
      set $curr = $curr + 1
    end
    printf "\n"
  end
  if $argc == 2
    if $arg0 == 2
      set $curr = $arg1->shape->slice_min
      set $max = $arg1->shape->slice_max
      printf "p3d: 3d_array '$arg1' dimensions (rows,columns):\n"
      while $curr <= $max
        printf "p3d: Index %d (rows, columns) = %ux%u,  %ux%u\n", $curr,\
        $arg1->t[$curr]->index_min, $arg1->t[$curr]->index_max,\
        $arg1->t[$curr]->m[$arg1->t[$curr]->index_min]->index_min,\
        $arg1->t[$curr]->m[$arg1->t[$curr]->index_max]->index_max
        set $curr = $curr + 1
      end
    else
      help p3d
    end
  end
end

document p3d
  Prints ADMB 3d_array contents.
  Syntax: pmat <ADMB 3darray>
  Examples:
  p3d d - Prints 3darray contents
  p3d 2 d - Prints 3darray dimensions
end
