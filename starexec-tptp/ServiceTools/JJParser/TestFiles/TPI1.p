%--------------------------------------------------------------------------------------------------
tpi(1,input,'Axioms/SYN001+1.ax').
fof(another,axiom,pp => qq).
fof(a,conjecture,qq).

tpi(1,input,'Axioms/SYN001+1.ax').
tpi(2,start_group,extra_axioms).
fof(another,axiom,q).
fof(a,conjecture,qq).
tpi(3,end_group,specifics).
tpi(4,execute,self).
tpi(5,delete,specifics).
fof(yet_another,axiom,r).
fof(a,conjecture,qq).
tpi(5,execute,self).
tpi(6,exit,exit(1)).

tpi(1,input,'/the/axioms.ax').
tpi(2,setenv,'CPU_LIMIT' = 300).
tpi(3,execute,'SZS_STATUS' = '/bin/paradox').
tpi(4,assert,$getenv('SZS_STATUS') != 'Unsatisfiable',unknown,['Axioms are unsatisfiable']).
fof(a,conjecture,p).
tpi(5,execute,'SZS_STATUS' = '/bin/eprover').
tpi(6,write,'Conjecture status: ' & $getenv('SZS_STATUS')).
tpi(7,exit,exit(1)).

tpi(1,input,'/the/axioms.ax').
tpi(2,setenv,'CPU_LIMIT' = 300).
tpi(3,execute_async,'ASYNC_SZS_STATUS' = '/bin/paradox').
fof(a,conjecture,p).
tpi(4,execute,'SZS_STATUS' = '/bin/eprover').
tpi(5,waitenv,'ASYNC_SZS_STATUS').
tpi(6,write,'Axioms status: ' & $getenv('ASYNC_SZS_STATUS') & ' Conjecture status: ' & $getenv('SZS_STATUS')).
tpi(7,exit,exit(1)).

tpi(1,start_group,all_axioms).
tpi(2,input,'/the/axioms.ax').
tpi(3,end_group,all_axioms).
fof(a,conjecture,p).
tpi(4,setenv,'CPU_LIMIT' = 300).
tpi(5,execute_async,'ASYNC_SZS_STATUS' = '/bin/eprover').
tpi(6,setenv,'SINE_OUTPUT' = '/tmp/FilteredFormulae').
tpi(7,execute,'/bin/SInE').
tpi(8,delete,all_axioms).
tpi(9,input,'/tmp/FilteredFormulae').
tpi(10,execute,'SZS_STATUS' = '/bin/eprover').
tpi(11,waitenv,'ASYNC_SZS_STATUS').
tpi(12,write,'All axioms status: ' & $getenv('ASYNC_SZS_STATUS') & ' Selected axioms status: ' & $getenv('SZS_STATUS')).
tpi(13,exit,exit(1)).

tpi(1,input,'/the/problem/file').
tpi(2,set_logic,qmltp('S4')).
tpi(3,execute,self).
tpi(4,set_logic,qmltp('D')).
tpi(5,execute,self).
tpi(6,exit,exit(1)).
%--------------------------------------------------------------------------------------------------
