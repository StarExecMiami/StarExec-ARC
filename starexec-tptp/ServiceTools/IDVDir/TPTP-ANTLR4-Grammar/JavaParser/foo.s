tff(decl_22,type,accessible_ki_world: ( ki_world * ki_world ) > $o ).
tff(decl_23,type,initial_ki_world: ki_world ).
tff(decl_24,type,in_ki_world: ki_world > $o ).
tff(decl_25,type,necessary: $o > $o ).
tff(decl_26,type,possible: $o > $o ).
tff(decl_27,type,apple: fruit ).
tff(decl_28,type,banana: fruit ).
tff(decl_29,type,healthy: fruit > $o ).
tff(decl_30,type,rotten: fruit > $o ).
tff(decl_31,type,w1: ki_world ).
tff(decl_32,type,w2: ki_world ).
tff(decl_33,type,d_to_fruit: d_fruit > fruit ).
tff(decl_34,type,d_apple: d_fruit ).
tff(decl_35,type,d_banana: d_fruit ).
tff(decl_36,type,esk1_0: ki_world ).
tff(decl_37,type,esk2_0: fruit ).
tff(decl_38,type,esk3_2: ( ki_world * $o ) > ki_world ).
tff(decl_39,type,esk4_1: fruit > d_fruit ).
tff(decl_40,type,esk5_1: fruit > d_fruit ).
tff(decl_41,type,esk6_2: ( ki_world * $o ) > ki_world ).
tff(prove_formulae,conjecture,! [X4: ki_world] : ( in_ki_world(X4) => ( ! [X10: fruit] : necessary(healthy(X10)) & rotten(apple) ) ) & ( in_ki_world(initial_ki_world) => ( rotten(banana) & healthy(apple) & possible(~ ( rotten(banana) )) ) ),file('IM_NTF_Finite.p',prove_formulae) ).
tff(fruity_worlds,axiom,! [X4: ki_world] : ( ( X4 = w1 ) | ( X4 = w2 ) ) & ( w1 != w2 ) & accessible_ki_world(w2,w1) & ( initial_ki_world = w2 ) & ! [X4: ki_world] : accessible_ki_world(X4,X4) & ( in_ki_world(w1) => ( ! [X5: d_fruit] : ( ( X5 = d_apple ) | ( X5 = d_banana ) ) & ( d_apple != d_banana ) & ! [X5: d_fruit] : ! [X6: d_fruit] : ( ( d_to_fruit(X5) = d_to_fruit(X6) ) => ( X5 = X6 ) ) & ! [X7: fruit] : ? [X8: d_fruit] : ( d_to_fruit(X8) = X7 ) & ( apple = d_to_fruit(d_apple) ) & ( banana = d_to_fruit(d_banana) ) & healthy(d_to_fruit(d_apple)) & healthy(d_to_fruit(d_banana)) & rotten(d_to_fruit(d_apple)) & ~ ( rotten(d_to_fruit(d_banana)) ) ) ) & ( in_ki_world(w2) => ( ! [X5: d_fruit] : ( ( X5 = d_apple ) | ( X5 = d_banana ) ) & ( d_apple != d_banana ) & ! [X5: d_fruit] : ! [X6: d_fruit] : ( ( d_to_fruit(X5) = d_to_fruit(X6) ) => ( X5 = X6 ) ) & ! [X9: fruit] : ? [X8: d_fruit] : ( d_to_fruit(X8) = X9 ) & ( apple = d_to_fruit(d_apple) ) & ( banana = d_to_fruit(d_banana) ) & healthy(d_to_fruit(d_apple)) & healthy(d_to_fruit(d_banana)) & rotten(d_to_fruit(d_apple)) & rotten(d_to_fruit(d_banana)) ) ),file('IM_NTF_Finite.p',fruity_worlds) ).
tff(possible_defn,axiom,! [X1: ki_world] : ( in_ki_world(X1) => ! [X2: $o] : ( possible(X2) <=> ? [X3: ki_world] : ( accessible_ki_world(X1,X3) & ( in_ki_world(X3) => (X2) ) ) ) ),file('IM_NTF_Finite.p',possible_defn) ).
tff(necessary_defn,axiom,! [X1: ki_world] : ( in_ki_world(X1) => ! [X2: $o] : ( necessary(X2) <=> ! [X3: ki_world] : ( accessible_ki_world(X1,X3) => ( in_ki_world(X3) => (X2) ) ) ) ),file('IM_NTF_Finite.p',necessary_defn) ).
tff(c_0_4,negated_conjecture,~ ( ! [X4: ki_world] : ( in_ki_world(X4) => ( ! [X10: fruit] : necessary(healthy(X10)) & rotten(apple) ) ) & ( in_ki_world(initial_ki_world) => ( rotten(banana) & healthy(apple) & possible(~ ( rotten(banana) )) ) ) ),inference(assume_negation,[status(cth)],[prove_formulae]) ).
tff(c_0_5,plain,! [X4: ki_world] : ( ( X4 = w1 ) | ( X4 = w2 ) ) & ( w1 != w2 ) & accessible_ki_world(w2,w1) & ( initial_ki_world = w2 ) & ! [X4: ki_world] : accessible_ki_world(X4,X4) & ( in_ki_world(w1) => ( ! [X5: d_fruit] : ( ( X5 = d_apple ) | ( X5 = d_banana ) ) & ( d_apple != d_banana ) & ! [X5: d_fruit] : ! [X6: d_fruit] : ( ( d_to_fruit(X5) = d_to_fruit(X6) ) => ( X5 = X6 ) ) & ! [X7: fruit] : ? [X8: d_fruit] : ( d_to_fruit(X8) = X7 ) & ( apple = d_to_fruit(d_apple) ) & ( banana = d_to_fruit(d_banana) ) & healthy(d_to_fruit(d_apple)) & healthy(d_to_fruit(d_banana)) & rotten(d_to_fruit(d_apple)) & ~ ( rotten(d_to_fruit(d_banana)) ) ) ) & ( in_ki_world(w2) => ( ! [X5: d_fruit] : ( ( X5 = d_apple ) | ( X5 = d_banana ) ) & ( d_apple != d_banana ) & ! [X5: d_fruit] : ! [X6: d_fruit] : ( ( d_to_fruit(X5) = d_to_fruit(X6) ) => ( X5 = X6 ) ) & ! [X9: fruit] : ? [X8: d_fruit] : ( d_to_fruit(X8) = X9 ) & ( apple = d_to_fruit(d_apple) ) & ( banana = d_to_fruit(d_banana) ) & healthy(d_to_fruit(d_apple)) & healthy(d_to_fruit(d_banana)) & rotten(d_to_fruit(d_apple)) & rotten(d_to_fruit(d_banana)) ) ),inference(fof_simplification,[status(thm)],[fruity_worlds]) ).
tff(c_0_6,negated_conjecture,( in_ki_world(initial_ki_world) | in_ki_world(esk1_0) ) & ( ~ ( rotten(banana) ) | ~ ( healthy(apple) ) | ~ ( possible(~ ( rotten(banana) )) ) | in_ki_world(esk1_0) ) & ( in_ki_world(initial_ki_world) | ~ ( necessary(healthy(esk2_0)) ) | ~ ( rotten(apple) ) ) & ( ~ ( rotten(banana) ) | ~ ( healthy(apple) ) | ~ ( possible(~ ( rotten(banana) )) ) | ~ ( necessary(healthy(esk2_0)) ) | ~ ( rotten(apple) ) ),inference(distribute,[status(thm)],[inference(skolemize,[status(esa)],[inference(variable_rename,[status(thm)],[inference(fof_nnf,[status(thm)],[c_0_4])])])]) ).
tff(c_0_7,plain,! [X18: ki_world] : ! [X19: ki_world] : ! [X20: d_fruit] : ! [X21: d_fruit] : ! [X22: d_fruit] : ! [X23: fruit] : ! [X25: d_fruit] : ! [X26: d_fruit] : ! [X27: d_fruit] : ! [X28: fruit] : ( ( ( X18 = w1 ) | ( X18 = w2 ) ) & ( w1 != w2 ) & accessible_ki_world(w2,w1) & ( initial_ki_world = w2 ) & accessible_ki_world(X19,X19) & ( ( X20 = d_apple ) | ( X20 = d_banana ) | ~ ( in_ki_world(w1) ) ) & ( ( d_apple != d_banana ) | ~ ( in_ki_world(w1) ) ) & ( ( d_to_fruit(X21) != d_to_fruit(X22) ) | ( X21 = X22 ) | ~ ( in_ki_world(w1) ) ) & ( ( d_to_fruit(esk4_1(X23)) = X23 ) | ~ ( in_ki_world(w1) ) ) & ( ( apple = d_to_fruit(d_apple) ) | ~ ( in_ki_world(w1) ) ) & ( ( banana = d_to_fruit(d_banana) ) | ~ ( in_ki_world(w1) ) ) & ( healthy(d_to_fruit(d_apple)) | ~ ( in_ki_world(w1) ) ) & ( healthy(d_to_fruit(d_banana)) | ~ ( in_ki_world(w1) ) ) & ( rotten(d_to_fruit(d_apple)) | ~ ( in_ki_world(w1) ) ) & ( ~ ( rotten(d_to_fruit(d_banana)) ) | ~ ( in_ki_world(w1) ) ) & ( ( X25 = d_apple ) | ( X25 = d_banana ) | ~ ( in_ki_world(w2) ) ) & ( ( d_apple != d_banana ) | ~ ( in_ki_world(w2) ) ) & ( ( d_to_fruit(X26) != d_to_fruit(X27) ) | ( X26 = X27 ) | ~ ( in_ki_world(w2) ) ) & ( ( d_to_fruit(esk5_1(X28)) = X28 ) | ~ ( in_ki_world(w2) ) ) & ( ( apple = d_to_fruit(d_apple) ) | ~ ( in_ki_world(w2) ) ) & ( ( banana = d_to_fruit(d_banana) ) | ~ ( in_ki_world(w2) ) ) & ( healthy(d_to_fruit(d_apple)) | ~ ( in_ki_world(w2) ) ) & ( healthy(d_to_fruit(d_banana)) | ~ ( in_ki_world(w2) ) ) & ( rotten(d_to_fruit(d_apple)) | ~ ( in_ki_world(w2) ) ) & ( rotten(d_to_fruit(d_banana)) | ~ ( in_ki_world(w2) ) ) ),inference(distribute,[status(thm)],[inference(shift_quantors,[status(thm)],[inference(skolemize,[status(esa)],[inference(variable_rename,[status(thm)],[inference(fof_nnf,[status(thm)],[c_0_5])])])])]) ).
tcf(c_0_8,negated_conjecture,in_ki_world(initial_ki_world) | in_ki_world(esk1_0),inference(split_conjunct,[status(thm)],[c_0_6]) ).
tcf(c_0_9,plain,initial_ki_world = w2,inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_10,plain,! [X1: ki_world] : ( X1 = w1 | X1 = w2 ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_11,negated_conjecture,in_ki_world(esk1_0) | in_ki_world(w2),inference(rw,[status(thm)],[c_0_8,c_0_9]) ).
tcf(c_0_12,plain,! [X3: ki_world] : ! [X1: ki_world] : ( X1 = w2 | X3 = w2 | X3 = X1 ),inference(spm,[status(thm)],[c_0_10,c_0_10]) ).
tcf(c_0_13,negated_conjecture,! [X1: ki_world] : ( esk1_0 = X1 | X1 = w2 | in_ki_world(w2) ),inference(spm,[status(thm)],[c_0_11,c_0_12]) ).
tcf(c_0_14,plain,apple = d_to_fruit(d_apple) | ~ ( in_ki_world(w1) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_15,negated_conjecture,! [X1: ki_world] : ( X1 = w2 | in_ki_world(w2) | in_ki_world(X1) ),inference(spm,[status(thm)],[c_0_11,c_0_13]) ).
tcf(c_0_16,plain,w1 != w2,inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_17,plain,apple = d_to_fruit(d_apple) | ~ ( in_ki_world(w2) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_18,plain,healthy(d_to_fruit(d_apple)) | ~ ( in_ki_world(w1) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_19,negated_conjecture,d_to_fruit(d_apple) = apple,inference(csr,[status(thm)],[inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_14,c_0_15]),c_0_16]),c_0_17]) ).
tcf(c_0_20,plain,healthy(d_to_fruit(d_apple)) | ~ ( in_ki_world(w2) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_21,plain,banana = d_to_fruit(d_banana) | ~ ( in_ki_world(w1) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_22,plain,banana = d_to_fruit(d_banana) | ~ ( in_ki_world(w2) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tff(c_0_23,negated_conjecture,in_ki_world(esk1_0) | ~ ( rotten(banana) ) | ~ ( healthy(apple) ) | ~ ( possible(~ ( rotten(banana) )) ),inference(split_conjunct,[status(thm)],[c_0_6]) ).
tcf(c_0_24,plain,healthy(apple) | ~ ( in_ki_world(w1) ),inference(rw,[status(thm)],[c_0_18,c_0_19]) ).
tcf(c_0_25,plain,healthy(apple) | ~ ( in_ki_world(w2) ),inference(rw,[status(thm)],[c_0_20,c_0_19]) ).
tff(c_0_26,plain,! [X13: ki_world] : ! [X14: $o] : ! [X16: $o] : ! [X17: ki_world] : ( ( accessible_ki_world(X13,esk3_2(X13,X14)) | ~ ( possible(X14) ) | ~ ( in_ki_world(X13) ) ) & ( ~ ( in_ki_world(esk3_2(X13,X14)) ) | (X14) | ~ ( possible(X14) ) | ~ ( in_ki_world(X13) ) ) & ( in_ki_world(X17) | ~ ( accessible_ki_world(X13,X17) ) | possible(X16) | ~ ( in_ki_world(X13) ) ) & ( ~ ( X16 ) | ~ ( accessible_ki_world(X13,X17) ) | possible(X16) | ~ ( in_ki_world(X13) ) ) ),inference(distribute,[status(thm)],[inference(shift_quantors,[status(thm)],[inference(skolemize,[status(esa)],[inference(variable_rename,[status(thm)],[inference(shift_quantors,[status(thm)],[inference(fof_nnf,[status(thm)],[possible_defn])])])])])]) ).
tcf(c_0_27,plain,accessible_ki_world(w2,w1),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_28,plain,rotten(d_to_fruit(d_banana)) | ~ ( in_ki_world(w2) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_29,negated_conjecture,d_to_fruit(d_banana) = banana,inference(csr,[status(thm)],[inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_21,c_0_15]),c_0_16]),c_0_22]) ).
tff(c_0_30,negated_conjecture,in_ki_world(esk1_0) | ~ ( rotten(banana) ) | ~ ( healthy(apple) ) | ~ ( possible(~ ( rotten(banana) )) ),inference(cn,[status(thm)],[c_0_23]) ).
tcf(c_0_31,negated_conjecture,healthy(apple),inference(csr,[status(thm)],[inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_24,c_0_15]),c_0_16]),c_0_25]) ).
tcf(c_0_32,plain,! [X1: ki_world] : ! [X2: $o] : ! [X3: ki_world] : ( in_ki_world(X1) | possible(X2) | ~ ( accessible_ki_world(X3,X1) ) | ~ ( in_ki_world(X3) ) ),inference(split_conjunct,[status(thm)],[c_0_26]) ).
tcf(c_0_33,plain,! [X1: ki_world] : ( X1 = w2 | accessible_ki_world(w2,X1) ),inference(spm,[status(thm)],[c_0_27,c_0_10]) ).
tcf(c_0_34,plain,rotten(banana) | ~ ( in_ki_world(w2) ),inference(rw,[status(thm)],[c_0_28,c_0_29]) ).
tff(c_0_35,negated_conjecture,in_ki_world(esk1_0) | ~ ( rotten(banana) ) | ~ ( possible(~ ( rotten(banana) )) ),inference(cn,[status(thm)],[inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_30,c_0_31])])]) ).
tcf(c_0_36,plain,! [X2: $o] : ! [X1: ki_world] : ( X1 = w2 | possible(X2) | in_ki_world(X1) ),inference(csr,[status(thm)],[inference(spm,[status(thm)],[c_0_32,c_0_33]),c_0_15]) ).
tcf(c_0_37,negated_conjecture,! [X1: ki_world] : ( X1 = w2 | rotten(banana) | in_ki_world(X1) ),inference(spm,[status(thm)],[c_0_34,c_0_15]) ).
tcf(c_0_38,plain,! [X5: d_fruit] : ( X5 = d_apple | X5 = d_banana | ~ ( in_ki_world(w1) ) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_39,plain,! [X5: d_fruit] : ( X5 = d_apple | X5 = d_banana | ~ ( in_ki_world(w2) ) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_40,plain,! [X7: fruit] : ( d_to_fruit(esk4_1(X7)) = X7 | ~ ( in_ki_world(w1) ) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_41,negated_conjecture,! [X1: ki_world] : ( X1 = w2 | in_ki_world(esk1_0) | in_ki_world(X1) ),inference(csr,[status(thm)],[inference(spm,[status(thm)],[c_0_35,c_0_36]),c_0_37]) ).
tcf(c_0_42,plain,rotten(d_to_fruit(d_apple)) | ~ ( in_ki_world(w1) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_43,plain,rotten(d_to_fruit(d_apple)) | ~ ( in_ki_world(w2) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_44,negated_conjecture,! [X5: d_fruit] : ( X5 = d_apple | X5 = d_banana ),inference(csr,[status(thm)],[inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_38,c_0_15]),c_0_16]),c_0_39]) ).
tcf(c_0_45,plain,! [X7: fruit] : ! [X1: ki_world] : ( d_to_fruit(esk4_1(X7)) = X7 | X1 = w2 | ~ ( in_ki_world(X1) ) ),inference(spm,[status(thm)],[c_0_40,c_0_10]) ).
tcf(c_0_46,negated_conjecture,esk1_0 = w2 | in_ki_world(esk1_0),inference(ef,[status(thm)],[c_0_41]) ).
tcf(c_0_47,negated_conjecture,in_ki_world(initial_ki_world) | ~ ( necessary(healthy(esk2_0)) ) | ~ ( rotten(apple) ),inference(split_conjunct,[status(thm)],[c_0_6]) ).
tcf(c_0_48,plain,rotten(apple) | ~ ( in_ki_world(w1) ),inference(rw,[status(thm)],[c_0_42,c_0_19]) ).
tcf(c_0_49,plain,rotten(apple) | ~ ( in_ki_world(w2) ),inference(rw,[status(thm)],[c_0_43,c_0_19]) ).
tcf(c_0_50,negated_conjecture,! [X5: d_fruit] : ( d_to_fruit(X5) = banana | X5 = d_apple ),inference(spm,[status(thm)],[c_0_29,c_0_44]) ).
tcf(c_0_51,negated_conjecture,! [X7: fruit] : ( d_to_fruit(esk4_1(X7)) = X7 | esk1_0 = w2 ),inference(spm,[status(thm)],[c_0_45,c_0_46]) ).
tcf(c_0_52,plain,healthy(d_to_fruit(d_banana)) | ~ ( in_ki_world(w1) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_53,plain,healthy(d_to_fruit(d_banana)) | ~ ( in_ki_world(w2) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tff(c_0_54,plain,! [X30: ki_world] : ! [X31: $o] : ! [X32: ki_world] : ! [X33: $o] : ( ( ~ ( necessary(X31) ) | ~ ( accessible_ki_world(X30,X32) ) | ~ ( in_ki_world(X32) ) | (X31) | ~ ( in_ki_world(X30) ) ) & ( accessible_ki_world(X30,esk6_2(X30,X33)) | necessary(X33) | ~ ( in_ki_world(X30) ) ) & ( in_ki_world(esk6_2(X30,X33)) | necessary(X33) | ~ ( in_ki_world(X30) ) ) & ( ~ ( X33 ) | necessary(X33) | ~ ( in_ki_world(X30) ) ) ),inference(distribute,[status(thm)],[inference(shift_quantors,[status(thm)],[inference(skolemize,[status(esa)],[inference(variable_rename,[status(thm)],[inference(shift_quantors,[status(thm)],[inference(fof_nnf,[status(thm)],[necessary_defn])])])])])]) ).
tcf(c_0_55,negated_conjecture,in_ki_world(w2) | ~ ( rotten(apple) ) | ~ ( necessary(healthy(esk2_0)) ),inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_47,c_0_9])]) ).
tcf(c_0_56,negated_conjecture,rotten(apple),inference(csr,[status(thm)],[inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_48,c_0_15]),c_0_16]),c_0_49]) ).
tcf(c_0_57,negated_conjecture,! [X7: fruit] : ( esk4_1(X7) = d_apple | esk1_0 = w2 | X7 = banana ),inference(spm,[status(thm)],[c_0_50,c_0_51]) ).
tcf(c_0_58,plain,healthy(banana) | ~ ( in_ki_world(w1) ),inference(rw,[status(thm)],[c_0_52,c_0_29]) ).
tcf(c_0_59,plain,healthy(banana) | ~ ( in_ki_world(w2) ),inference(rw,[status(thm)],[c_0_53,c_0_29]) ).
tcf(c_0_60,plain,! [X1: ki_world] : ( necessary($true) | ~ ( in_ki_world(X1) ) ),inference(cn,[status(thm)],[inference(cn,[status(thm)],[inference(split_conjunct,[status(thm)],[c_0_54])])]) ).
tcf(c_0_61,negated_conjecture,in_ki_world(w2) | ~ ( necessary(healthy(esk2_0)) ),inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_55,c_0_56])]) ).
tcf(c_0_62,negated_conjecture,! [X7: fruit] : ( esk1_0 = w2 | X7 = banana | apple = X7 ),inference(rw,[status(thm)],[inference(spm,[status(thm)],[c_0_51,c_0_57]),c_0_19]) ).
tcf(c_0_63,negated_conjecture,healthy(banana),inference(csr,[status(thm)],[inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_58,c_0_15]),c_0_16]),c_0_59]) ).
cnf(c_0_64,negated_conjecture,necessary($true),inference(csr,[status(thm)],[inference(spm,[status(thm)],[c_0_60,c_0_11]),c_0_60]) ).
tcf(c_0_65,plain,~ ( rotten(d_to_fruit(d_banana)) ) | ~ ( in_ki_world(w1) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tcf(c_0_66,negated_conjecture,esk2_0 = apple | esk1_0 = w2 | in_ki_world(w2),inference(cn,[status(thm)],[inference(rw,[status(thm)],[inference(rw,[status(thm)],[inference(spm,[status(thm)],[c_0_61,c_0_62]),c_0_63]),c_0_64])]) ).
tcf(c_0_67,plain,~ ( rotten(banana) ) | ~ ( in_ki_world(w1) ),inference(rw,[status(thm)],[c_0_65,c_0_29]) ).
tcf(c_0_68,negated_conjecture,esk1_0 = w2 | esk2_0 = apple | rotten(banana),inference(spm,[status(thm)],[c_0_34,c_0_66]) ).
tcf(c_0_69,negated_conjecture,esk1_0 = w2 | in_ki_world(w1),inference(sr,[status(thm)],[inference(spm,[status(thm)],[c_0_46,c_0_10]),c_0_16]) ).
tcf(c_0_70,negated_conjecture,esk2_0 = apple | esk1_0 = w2,inference(csr,[status(thm)],[inference(spm,[status(thm)],[c_0_67,c_0_68]),c_0_69]) ).
tcf(c_0_71,negated_conjecture,esk1_0 = w2 | in_ki_world(w2),inference(cn,[status(thm)],[inference(rw,[status(thm)],[inference(rw,[status(thm)],[inference(spm,[status(thm)],[c_0_61,c_0_70]),c_0_31]),c_0_64])]) ).
tcf(c_0_72,negated_conjecture,esk1_0 = w2 | rotten(banana),inference(spm,[status(thm)],[c_0_34,c_0_71]) ).
tcf(c_0_73,negated_conjecture,esk1_0 = w2,inference(csr,[status(thm)],[inference(spm,[status(thm)],[c_0_67,c_0_72]),c_0_69]) ).
tff(c_0_74,negated_conjecture,~ ( rotten(banana) ) | ~ ( healthy(apple) ) | ~ ( possible(~ ( rotten(banana) )) ) | ~ ( necessary(healthy(esk2_0)) ) | ~ ( rotten(apple) ),inference(split_conjunct,[status(thm)],[c_0_6]) ).
tcf(c_0_75,negated_conjecture,in_ki_world(w2),inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_11,c_0_73])]) ).
tff(c_0_76,negated_conjecture,~ ( rotten(apple) ) | ~ ( rotten(banana) ) | ~ ( healthy(apple) ) | ~ ( possible(~ ( rotten(banana) )) ) | ~ ( necessary(healthy(esk2_0)) ),inference(cn,[status(thm)],[c_0_74]) ).
tcf(c_0_77,plain,rotten(banana),inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_34,c_0_75])]) ).
tcf(c_0_78,plain,! [X7: fruit] : ( d_to_fruit(esk5_1(X7)) = X7 | ~ ( in_ki_world(w2) ) ),inference(split_conjunct,[status(thm)],[c_0_7]) ).
tff(c_0_79,negated_conjecture,~ ( rotten(banana) ) | ~ ( possible(~ ( rotten(banana) )) ) | ~ ( necessary(healthy(esk2_0)) ),inference(cn,[status(thm)],[inference(cn,[status(thm)],[inference(rw,[status(thm)],[inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_76,c_0_56])]),c_0_31])])]) ).
tcf(c_0_80,plain,! [X2: $o] : ( possible(X2) | in_ki_world(w1) | ~ ( in_ki_world(w2) ) ),inference(spm,[status(thm)],[c_0_32,c_0_27]) ).
tcf(c_0_81,plain,~ ( in_ki_world(w1) ),inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_67,c_0_77])]) ).
tcf(c_0_82,plain,! [X7: fruit] : d_to_fruit(esk5_1(X7)) = X7,inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_78,c_0_75])]) ).
tcf(c_0_83,negated_conjecture,~ ( possible($false) ) | ~ ( necessary(healthy(esk2_0)) ),inference(cn,[status(thm)],[inference(cn,[status(thm)],[inference(rw,[status(thm)],[inference(rw,[status(thm)],[c_0_79,c_0_77]),c_0_77])])]) ).
cnf(c_0_84,plain,possible(X2),inference(sr,[status(thm)],[inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_80,c_0_75])]),c_0_81]) ).
tcf(c_0_85,negated_conjecture,! [X7: fruit] : ( esk5_1(X7) = d_apple | X7 = banana ),inference(spm,[status(thm)],[c_0_50,c_0_82]) ).
tcf(c_0_86,negated_conjecture,~ ( necessary(healthy(esk2_0)) ),inference(cn,[status(thm)],[inference(rw,[status(thm)],[c_0_83,c_0_84])]) ).
tcf(c_0_87,negated_conjecture,! [X7: fruit] : ( X7 = banana | apple = X7 ),inference(rw,[status(thm)],[inference(spm,[status(thm)],[c_0_82,c_0_85]),c_0_19]) ).
tcf(c_0_88,negated_conjecture,esk2_0 = apple,inference(cn,[status(thm)],[inference(rw,[status(thm)],[inference(rw,[status(thm)],[inference(spm,[status(thm)],[c_0_86,c_0_87]),c_0_63]),c_0_64])]) ).
cnf(c_0_89,negated_conjecture,$false,inference(cn,[status(thm)],[inference(rw,[status(thm)],[inference(rw,[status(thm)],[inference(spm,[status(thm)],[c_0_86,c_0_88]),c_0_31]),c_0_64])]),[proof] ).
