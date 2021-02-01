package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.stage.Stage;
import model.*;

public class ComputerBuilderController extends Controller<ComputerBuilder> {
    public final ComputerBuilder getComputerBuilder() { return model; } 
    
    @FXML public void handleVCatalogue(ActionEvent event) throws Exception{
        ViewLoader.showStage(getComputerBuilder().getCatalogue(), "/view/catalogue.fxml", "Catalogue", new Stage());
    }
    
    @FXML public void handleVBuild(ActionEvent event) throws Exception{
        ViewLoader.showStage(getComputerBuilder().getBuild(), "/view/build.fxml", "Current Build", new Stage());
    }
       
    @FXML public void handleQuit(ActionEvent event) throws Exception{
        stage.close();
    }
}