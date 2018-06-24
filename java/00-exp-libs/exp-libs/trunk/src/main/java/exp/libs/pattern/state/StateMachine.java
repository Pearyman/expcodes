package exp.libs.pattern.state;

import exp.libs.pattern.state.impl.Created;
import exp.libs.pattern.state.impl.Running;
import exp.libs.pattern.state.impl.Sleep;
import exp.libs.pattern.state.impl.Stop;


/**
 * <PRE>
 * 状态模式 - 状态机
 * </PRE>
 * <B>PROJECT：</B> exp-libs
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2015-12-27
 * @author    EXP: www.exp-blog.com
 * @since     jdk版本：jdk1.6
 */
public class StateMachine {

	private final Created createdState;
	
	private final Running runState;
	
	private final Sleep sleepState;
	
	private final Stop stopState;
	
	protected IState state;
	
	protected StateMachine() {
		this.createdState = new Created(this);
		this.runState = new Running(this);
		this.sleepState = new Sleep(this);
		this.stopState = new Stop(this);
		
		this.state = createdState;
	}
	
	public final void setState(IState state) {
		this.state = state;
	}
	
	public final IState getState() {
		return state;
	}

	public final Created getCreatedState() {
		return createdState;
	}

	public final Running getRunState() {
		return runState;
	}

	public final Sleep getSleepState() {
		return sleepState;
	}

	public final Stop getStopState() {
		return stopState;
	}
	
}
