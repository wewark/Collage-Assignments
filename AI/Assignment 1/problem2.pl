integrate(B,B,_,0).
integrate(A,B,X,R):-
	A<B,
	Next is A+X,
	integrate(Next,B,X,T),
	R is T + ((X/2)*(A*A))+((X/2)*(Next*Next)).