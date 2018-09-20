package exp.ali.math.question1;

/**
 * <PRE>
 * Qc：【问题描述】
 * 建模题：对比单卖和捆绑销售下的利润期望。
 * 
 * 假设耳机（产品1）和音箱（产品2）的单件销售的单位成本分别是c1和c2（包含生产、储存、运输、促销等所有成本）。
 * 一个访问店铺的客户对两件产品的心理价值分别是均匀分布在[0, u1]和[0, u2]的区间上随机变量S1和S2。
 * 假设S1和S2相互独立。
 * 
 * 本题有三小问。
 * 1. 如何分别设定产品价格p1和p2，以最大化每个到访客户带来的利润期望。
 *    这里假设c1 <u1；当且仅当p1 ≤ S1时，客户会购买一件产品1；用户不买的话不计损失。
 *    对产品2做类似假设。
 *    请以公式形式给出最优价格 *p1 和 *p2 以及对应的最大利润期望 *r1 和 *r2。
 *    
 * 2. 现在假设产品1和2捆绑销售，成本是c12 = t(c1 + c2)。
 *    因为节省了包装和运输成本，所以假设0 < t < 1。其余的条件不变。
 *    请以公式形式给出捆绑下的最优价 *p12
 *    
 * 3. 单卖和捆绑销售，哪个利润更优，还是不一定? 为什么?
 * 
 * </PRE>
 * <br/><B>PROJECT : </B> Ali-Math-Competition
 * <br/><B>SUPPORT : </B> <a href="http://www.exp-blog.com" target="_blank">www.exp-blog.com</a> 
 * @version   2018-09-19
 * @author    EXP: 272629724@qq.com
 * @since     jdk版本：jdk1.6
 */
public class Qc {

	/**
	 * <PRE>
	 * Qc：【解题思路】
	 * 进一步衍化成运筹学的【随机规划】问题
	 * 
	 * 
	 */
}
