set pagination off
set logging file gdb.output
set logging on

# This line is a comment
break model_parameters::userfunction
    command 1
    where
    p fpe_check()
    continue
end

run

set logging off
quit
