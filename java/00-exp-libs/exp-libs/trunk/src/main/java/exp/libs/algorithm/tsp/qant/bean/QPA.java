package exp.libs.algorithm.tsp.qant.bean;


/**
 * Quantum Probability Amplitude
 * 量子概率幅（量子比特，路径信息素的概率幅）
 *  量子态|ψ> = α|0> + β|1>  
 *  其中α^2 + β^2 = 1, 含义为对量子态|ψ>测量时，有α^2的概率坍缩到基态|0>，有β^2的概率坍缩到基态|1>
 *  亦即  α^2为不选择路径的概率，β^2是选择路径的概率
 */
class QPA {

	/** 量子概率幅初始值(1/√2) */
	private final static double DEFAULT_QPA = 1.0D / Math.sqrt(2.0D);
	
	/** 路径信息素的α概率幅(不选择的概率)  */
	private double alpha;
	
	/** 路径信息素的β概率幅(选择的概率)  */
	private double beta;
	
	protected QPA() {
		this.alpha = DEFAULT_QPA;
		this.beta = DEFAULT_QPA;
	}

	protected double getAlpha() {
		return alpha;
	}

	protected void setAlpha(double alpha) {
		this.alpha = alpha;
	}

	protected double getBeta() {
		return beta;
	}

	protected void setBeta(double beta) {
		this.beta = beta;
	}
	
}
