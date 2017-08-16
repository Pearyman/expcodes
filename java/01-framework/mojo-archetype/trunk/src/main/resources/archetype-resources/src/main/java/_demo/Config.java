#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
package ${package}._demo;

import com.kt.explibs.envm.Charset;
import com.kt.explibs.utils.StrUtils;
import com.kt.explibs.warp.conf.xml.XConfig;
import com.kt.explibs.warp.conf.xml.XConfigFactory;
import com.kt.explibs.warp.db.sql.bean.DataSourceBean;
import com.kt.explibs.warp.net.sock.bean.SocketBean;

/**
 * <PRE>
 * XML配置加载器实例
 * </PRE>
 * <B>项    目：</B> xxxxxxx
 * <B>技术支持：</B>广东凯通软件开发技术有限公司 (c) 2017
 * @version   1.0 2017-07-12
 * @author    ??：??@gdcattsoft.com
 * @since     jdk版本：jdk1.6
 */
public class Config {
	
	/** 程序配置文件（全量配置） */
	private final static String APP_CONF = "./conf/[prj-name]_app_cfg.dat";
	
	/** 工程配置文件（常用配置） */
	private final static String USE_CONF = "./conf/[prj-name]_conf.xml";
	
	public final static String DEFAULT_CHARSET = Charset.UTF8;
	
	private final static String SOCK_NAME = "TEST-SOCK";
	
	private final static String DS_NAME = "TEST-DS";
	
	/** XML配置加载器 */
	private XConfig xConf;
	
	private static volatile Config instance;
	
	private Config() {
		this.xConf = XConfigFactory.createConfig("MSTP");
		xConf.loadConfFile(APP_CONF);
		xConf.loadConfFile(USE_CONF);
	}
	
	public static Config getInstn() {
		if(instance == null) {
			synchronized (Config.class) {
				if(instance == null) {
					instance = new Config();
				}
			}
		}
		return instance;
	}
	
	public void reflash(long timeMillis) {
		xConf.reflash(timeMillis);
	}
	
	public void clear() {
		xConf.destroy();
	}
	
	public SocketBean getSocket() {
		return xConf.getSocketBean(SOCK_NAME);
	}
	
	public DataSourceBean getDataSource() {
		return xConf.getDataSourceBean(DS_NAME);
	}
	
	public String getDriverName() {
		return xConf.getVal("config/datasources/datasource@" + DS_NAME + "/driver");
	}
	
	public String getEmsName() {
		return xConf.getVal("config/bases/base@MSTP/emsname");
	}
	
	public String getWsdl() {
		String ip = xConf.getVal("config/bases/base@ISP-WEBSERVICE/ip");
		String port = xConf.getVal("config/bases/base@ISP-WEBSERVICE/port");
		String uri = xConf.getVal("config/bases/base@ISP-WEBSERVICE/name");
		return StrUtils.concat("http://", ip, ":", port, "/", uri, "?wsdl");
	}
	
}