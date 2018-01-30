package exp.bilibili.protocol.xhr;

import java.util.Iterator;

import exp.bilibili.plugin.Config;
import exp.bilibili.plugin.envm.LotteryType;
import exp.bilibili.plugin.utils.UIUtils;
import exp.bilibili.protocol.cookie.CookiesMgr;
import exp.bilibili.protocol.cookie.HttpCookie;
import exp.libs.utils.other.StrUtils;

/**
 * <PRE>
 * 小电视抽奖
 * </PRE>
 * <B>PROJECT：</B> bilibili-plugin
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2017-12-17
 * @author    EXP: 272629724@qq.com
 * @since     jdk版本：jdk1.6
 */
public class LotteryTV extends _Lottery {
	
	/** 小电视抽奖URL */
	private final static String TV_JOIN_URL = Config.getInstn().TV_JOIN_URL();
	
	/** 私有化构造函数 */
	protected LotteryTV() {}
	
	/**
	 * 小电视抽奖 FIXME 某个用户是否成功
	 * @param roomId
	 * @param raffleId
	 * @return
	 */
	public static void toLottery(int roomId, String raffleId) {
		int cnt = 0;
		Iterator<HttpCookie> cookieIts = CookiesMgr.INSTN().ALL();
		while(cookieIts.hasNext()) {
			HttpCookie cookie = cookieIts.next();
			String reason = join(LotteryType.TV, cookie, TV_JOIN_URL, roomId, raffleId);
			if(StrUtils.isEmpty(reason)) {
				log.info("[{}] 参与直播间 [{}] 抽奖成功", cookie.NICKNAME(), roomId);
				cnt++;
				
			} else {
				log.info("[{}] 参与直播间 [{}] 抽奖失败", cookie.NICKNAME(), roomId);
				UIUtils.statistics("失败(", reason, "): 直播间 [", roomId, 
						"],账号[", cookie.NICKNAME(), "]");
			}
		}
		
		if(cnt > 0) {
			UIUtils.statistics("成功(小电视x", cnt, "): 直播间 [", roomId, "]");
			UIUtils.updateLotteryCnt(cnt);
		}
	}
	
}
