package exp.crawler.qq.cache;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

import exp.libs.warp.net.webkit.WebBrowser;
import exp.libs.warp.net.webkit.WebDriverType;
import exp.libs.warp.net.webkit.WebUtils;
import exp.crawler.qq.bean.QQCookie;


/**
 * <PRE>
 * 浏览器驱动管理器
 * </PRE>
 * <B>PROJECT：</B> bilibili-plugin
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2017-12-17
 * @author    EXP: 272629724@qq.com
 * @since     jdk版本：jdk1.6
 */
public class Browser {
	
	private WebBrowser browser;
	
	private QQCookie qqCookie;
	
	private static volatile Browser instance;
	
	private Browser() {
		this.qqCookie = new QQCookie();
	}
	
	private static Browser INSTN() {
		if(instance == null) {
			synchronized (Browser.class) {
				if(instance == null) {
					instance = new Browser();
				}
			}
		}
		return instance;
	}
	
	public static void init(boolean loadImages) {
		INSTN()._reset(loadImages);
	}
	
	public static void reset(boolean loadImages) {
		INSTN()._reset(loadImages);
	}
	
	/**
	 * 重置浏览器驱动
	 * @param loadImages
	 * @return
	 */
	private void _reset(boolean loadImages) {
		_backupCookies();
		_quit();
		browser = new WebBrowser(WebDriverType.PHANTOMJS, loadImages);
		recoveryCookies();
	}
	
	public static WebDriver DRIVER() {
		return INSTN()._DRIVER();
	}
	
	private WebDriver _DRIVER() {
		return (browser == null ? null : browser.getDriver());
	}
	
	public static QQCookie COOKIE() {
		return INSTN()._COOKIE();
	}
	
	private QQCookie _COOKIE() {
		return qqCookie;
	}
	
	public static String GTK() {
		return INSTN()._GTK();
	}
	
	private String _GTK() {
		return qqCookie.GTK();
	}
	
	public static void open(String url) {
		INSTN()._open(url);
	}
	
	private void _open(String url) {
		if(browser == null){
			_reset(false);	// 默认不加载图片
		}
		browser.open(url);
	}
	
	public static void refresh() {
		INSTN()._refresh();
	}
	
	private void _refresh() {
		if(browser != null){
			browser.refresh();
		}
	}
	
	public static void quit() {
		INSTN()._quit();
	}
	
	/**
	 * 退出浏览器
	 */
	private void _quit() {
		if(browser != null) {
			browser.quit();
			browser = null;
		}
	}
	
	public static String getCurURL() {
		return INSTN()._getCurURL();
	}
	
	private String _getCurURL() {
		return (browser == null ? "" : browser.getCurURL());
	}
	
	public static String getPageSource() {
		return INSTN()._getPageSource();
	}
	
	private String _getPageSource() {
		return (browser == null ? "" : browser.getPageSource());
	}
	
	public static void backupCookies() {
		INSTN()._backupCookies();
	}
	
	private void _backupCookies() {
		if(browser != null) {
			qqCookie.clear();
			qqCookie.add(browser.getCookies());
		}
	}
	
	private void recoveryCookies() {
		if(browser != null) {
			browser.clearCookies();
			browser.addCookies(qqCookie.toSeleniumCookies());
		}
	}
	
	public static void clearCookies() {
		INSTN()._clearCookies();
	}
	
	private void _clearCookies() {
		qqCookie.clear();
		if(browser != null) {
			browser.clearCookies();
		}
	}
	
	public static WebElement findElement(By by) {
		return INSTN()._findElement(by);
	}
	
	private WebElement _findElement(By by) {
		return WebUtils.findElement(browser.getDriver(), by);
	}
	
	public static void fill(WebElement input, String data) {
		WebUtils.fill(input, data);
	}
	
	public static void click(WebElement button) {
		INSTN()._click(button);
	}
	
	private void _click(WebElement button) {
		WebUtils.click(browser.getDriver(), button);
	}
	
	public static void switchToFrame(By frame) {
		INSTN()._switchToFrame(frame);
	}
	
	private void _switchToFrame(By frame) {
		WebUtils.switchToFrame(browser.getDriver(), frame);
	}
	
	public static void switchToParentFrame() {
		INSTN()._switchToParentFrame();
	}
	
	private void _switchToParentFrame() {
		WebUtils.switchToParentFrame(browser.getDriver());
	}
	
	public static void switchToTopFrame() {
		INSTN()._switchToTopFrame();
	}
	
	private void _switchToTopFrame() {
		WebUtils.switchToTopFrame(browser.getDriver());
	}
	
	public static void scrollToBottom() {
		INSTN()._scrollToBottom();
	}
	
	private void _scrollToBottom() {
		WebUtils.scrollToBottom(browser.getDriver());
	}
	
	
}