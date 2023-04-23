% farmer fox goose beer
goal([0,0,0,0]).

mw([X,X,Goat,Cabage], [Y,Y,Goat,Cabage]):- 
    X<=1, 
    Y is 1-X.
mg([X,Wolf,X,Cabage], [Y,Wolf,Y,Cabage]):- 
    X<=1, 
    Y is 1-X .
mv([X,Wolf,Goat,X], [Y,Wolf,Goat,Y]):- 
    X<=1, 
    Y is 1-X .
mn([X,Wolf,Goat,Cabage], [Y,Wolf,Goat,Cabage]):- 
    X<=1, 
    Y is 1-X .

en([X,Y,Y,_]).
en([X,_,Y,Y]).

ts(X,Y):- mw(X,Y),\+ en(Y).
ts(X,Y):- mg(X,Y),\+ en(Y).
ts(X,Y):- mv(X,Y),\+ en(Y).
ts(X,Y):- mn(X,Y),\+ en(Y).

dfs(X,P,[X|P]):- goal(X).
dfs(X,P,Path):- ts(X,Y),X\=Y,\+ member(Y,P),dfs(Y,[X|P],Path).