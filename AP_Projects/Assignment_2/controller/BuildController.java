package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import model.*;

public class BuildController extends Controller<Build>{
    public final Build getBuild() { return model; }
    @FXML private Button RemoveFromBuildBtn;
    @FXML private TableView<Part> buildTv;
    @FXML private TableColumn<Part, String> priceClm;
    @FXML private Text totalCost;
    
    @FXML private void initialize() {
        //Populates price column with custom format
        priceClm.setCellValueFactory(cellData -> cellData.getValue().priceProperty().asString("$%.2f"));
        buildTv.getSelectionModel().selectedItemProperty().addListener(
          (observable, oldPart, newPart) -> {
          RemoveFromBuildBtn.setDisable(newPart == null);
          totalCost.setText("$"+formatted(getBuild().totalPrice()));
          });
    
        buildTv.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        totalCost.setText("$"+formatted(getBuild().totalPrice()));
        
    }
    
    
    
    @FXML public void handleRemoveFromBuild(ActionEvent event) throws Exception {
        List<Part> items =  new ArrayList (buildTv.getSelectionModel().getSelectedItems());
        getBuild().remove(items);
        totalCost.setText("$"+formatted(getBuild().totalPrice()));
    }
    
    @FXML public void handleCheckBuildBtn(ActionEvent event) throws Exception {
        ViewLoader.showStage(getBuild(), "/view/buildcheck.fxml", "Build Vailidity Status", new Stage());
    }
    
    @FXML public void handleCloseBuildBtn(ActionEvent event) throws Exception{
        stage.close();
    }
    
    private String formatted(double money) {
        return new DecimalFormat("###,##0.00").format(money);
    }
}
