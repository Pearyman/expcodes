package exp.libs.pattern.state;

/**
 * <PRE>
 * 状态接口.
 * </PRE>
 * <B>PROJECT：</B> exp-libs
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2015-12-27
 * @author    EXP: www.exp-blog.com
 * @since     jdk版本：jdk1.6
 */
public abstract class IState {

	protected StateMachine stateMachine;
	
	public IState(StateMachine stateMachine) {
		this.stateMachine = stateMachine;
	}
	
	public abstract String getDes();
	
	public abstract boolean _start();
	
	public abstract boolean _pause();
	
	public abstract boolean _resume();
	
	public abstract boolean _stop();

}
