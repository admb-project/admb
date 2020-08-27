set pagination off
set logging file gdb.output
set logging on

define fpe
    call fpe_init()
    finish
    call fpe_check()
    continue
end

# This line is a comment
break model_parameters::preliminary_calculations
    command 1
    fpe
end

break model_parameters::set_runtime
    command 2
    fpe
end

break model_parameters::userfunction
    command 3
    fpe
end

break model_parameters::report
    command 4
    fpe
end

break model_parameters::final_calcs
    command 5
    fpe
end

run

set logging off
quit
