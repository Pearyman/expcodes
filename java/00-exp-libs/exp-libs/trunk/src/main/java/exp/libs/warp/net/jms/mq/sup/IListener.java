package exp.libs.warp.net.jms.mq.sup;

import javax.jms.MessageListener;

/**监听接口<br>
 * 使用场景：获取关注的消息内容时使用<br>
 * 步骤: 监听消息时,需要实现该类,并将实现类制定为监听类。<br>
 * 例：consumer.setMessageListener(new Listener());<br>
 * <B>PROJECT：</B> exp-libs
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2016-02-14
 * @author    EXP: www.exp-blog.com
 * @since     jdk版本：jdk1.6
 */
public interface  IListener extends MessageListener{
	//public void onMessage(Message message);
	
	/**
	 * 或许仅仅是为了使用I****来表示接口
	 */
}
