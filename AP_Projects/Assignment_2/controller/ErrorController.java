package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import model.*;

public class ErrorController extends Controller<Catalogue> {
    public final Catalogue getCatalogue() { return model; }
    
    @FXML public void handleCloseBtn(ActionEvent event) throws Exception {
        stage.close();
    }
    
}
