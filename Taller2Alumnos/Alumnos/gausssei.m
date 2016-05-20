function [X] = gausssei(A,b,x0)
    D = diag(diag(A));
    L = -1*tril(A,-1);
    U = -1*triu(A,1);
    C = inv(D-L)*b;
    T = inv(-L+D)*U;
    X = x0;
    while (norm(A*X-b) > 0.000001)
        X = T*X + C;
    end
end
