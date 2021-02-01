package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import model.Catalogue;

public class AddToCatalogueController extends Controller<Catalogue> {
    public final Catalogue getCatalogue() { return model; }
    @FXML private TextField typeTf;
    @FXML private TextField nameTf;
    @FXML private TextField priceTf;
    @FXML public void handleCloseBtn(ActionEvent event) throws Exception {
        stage.close();
    }

    @FXML public void handleAddToParts(ActionEvent event) throws Exception{
        try {
            double p = Double.parseDouble(priceTf.getText());
       //Will prevent negative prices as input    
            if (p < 0) {
                 ViewLoader.showStage(getCatalogue(), "/view/error.fxml", "Incorrect Input", new Stage());
            } else {
            getCatalogue().addPart(nameTf.getText(), typeTf.getText(), p);
            stage.close();
            }
       //Cataches numberFormat exception
    } catch( Exception e ) {
         ViewLoader.showStage(getCatalogue(), "/view/error.fxml", "Incorrect Input", new Stage());
    }
    
    }
    
}