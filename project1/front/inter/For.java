package inter;

import symbols.*;
import inter.*;

public class For extends Stmt {

    private Expr mY;
    private Stmt mX, mZ;
    private Stmt mStmt;

    public For() {
        mX = null;
        mY = null;
        mZ = null;
        mStmt = null;
    }

    public void init(Stmt x, Expr y, Stmt z, Stmt stmt) {
        mX = x;
        mY = y;
        mZ = z;
        mStmt = stmt;

        // the second expression needs to be a boolean
        if(y != null && y.type != Type.Bool) y.error("boolean expression required in second position of for loop");
    }

    @Override
    public void gen(int b, int a) {
        after = a;

        // generate a label at the top of the loop
        final int loopLabel = newlabel();

        if(mX != null) {
            mX.gen(b, loopLabel);
        }
        emitlabel(loopLabel);

        if(mY != null) {
            mY.jumping(0, a);
        }

        // create before and after labels for internal statement
        final int statementB = newlabel();
        final int statementA = newlabel();

        // emit label before statement
        emitlabel(statementB);
        // generate intermediate for internal statements
        mStmt.gen(statementB, statementA);
        // emit label after statement
        emitlabel(statementA);

        if(mZ != null) {
            final int zLabel = newlabel();
            mZ.gen(statementA, zLabel);
            emitlabel(zLabel);
        }
        emit("goto L" + loopLabel);
    }



}
