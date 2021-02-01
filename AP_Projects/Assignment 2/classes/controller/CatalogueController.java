package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import java.util.ArrayList;
import java.util.List;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;
import model.*;
import javafx.scene.control.SelectionMode.*;

public class CatalogueController extends Controller<Catalogue> {
    public final Catalogue getCatalogue() { return model; } 
    @FXML private TableColumn<Part, String> priceClm;
    @FXML private TableView<Part> catalogueTv;
    @FXML private Button addToBuildBtn;
    @FXML private Button removeFromCatalogueBtn;
    @FXML private TextField typeTf;
    @FXML private TextField minTf;
    @FXML private TextField maxTf;
    
    @FXML private void initialize() {
      priceClm.setCellValueFactory(cellData -> cellData.getValue().priceProperty().asString("$%.2f"));
      catalogueTv.getSelectionModel().selectedItemProperty().addListener(
          (observable, oldPart, newPart) -> 
          addToBuildBtn.setDisable(newPart == null));
      catalogueTv.getSelectionModel().selectedItemProperty().addListener(
          (observable, oldPart, newPart) -> 
          removeFromCatalogueBtn.setDisable(newPart == null));
      catalogueTv.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);     
      //Filter uses listeners for each field
      typeTf.textProperty().addListener((observable, oldValue, newValue) 
              -> getCatalogue().filterList(newValue, minTf.getText(), maxTf.getText()));
      minTf.textProperty().addListener((observable, oldValue, newValue) 
              -> getCatalogue().filterList(typeTf.getText(), newValue, maxTf.getText()));
      maxTf.textProperty().addListener((observable, oldValue, newValue) 
              -> getCatalogue().filterList(typeTf.getText(), minTf.getText(), newValue));
      
    
    }
    
    
    @FXML public void handleCloseBtn(ActionEvent event) throws Exception {
        stage.close();
    }
    
    @FXML public void handleAddToBuild(ActionEvent event) throws Exception {
        List items =  new ArrayList (catalogueTv.getSelectionModel().getSelectedItems());
    
        getCatalogue().addToBuild(items);
    }
    
    @FXML public void handleRemoveFromCatalogue(ActionEvent event) throws Exception {
        List items =  new ArrayList (catalogueTv.getSelectionModel().getSelectedItems());
        
        getCatalogue().remove(items);
    }
    
    @FXML public void handleAddToCatalogue(ActionEvent event) throws Exception {
        ViewLoader.showStage(getCatalogue(), "/view/addtocatalogue.fxml", "Add New Part to Catalogue", new Stage());
    }
}
