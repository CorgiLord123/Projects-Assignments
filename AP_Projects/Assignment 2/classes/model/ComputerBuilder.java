package model;

import javafx.fxml.FXML;
import javafx.scene.control.*;

public class ComputerBuilder {
	private final Catalogue catalogue;
	private final Build build;
	
	public ComputerBuilder() {
		
		build = new Build();
		catalogue = new Catalogue(build);

	}
	
	public Catalogue getCatalogue() {
		return this.catalogue;
	}
	
	public Build getBuild() {
		return this.build;
	}
	
	

}
