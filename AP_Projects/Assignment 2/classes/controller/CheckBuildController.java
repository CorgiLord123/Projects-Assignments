package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.text.Text;
import model.*;

public class CheckBuildController extends Controller<Build>{
    public final Build getBuild() { return model; }
    @FXML private Text noCPU;
    @FXML private Text noMotherboard;
    @FXML private Text noRAM;
    @FXML private Text noCase;
    @FXML private Text noStorage;
    @FXML private Text valid;
    @FXML private void initialize() {
        noCPU.setVisible(!getBuild().hasPartOfType("CPU"));
        noMotherboard.setVisible(!getBuild().hasPartOfType("motherboard"));
        noRAM.setVisible(!getBuild().hasPartOfType("memory"));
        noCase.setVisible(!getBuild().hasPartOfType("case"));
        noStorage.setVisible(!getBuild().hasPartOfType("storage"));
        valid.setVisible(getBuild().isValid());
    }
    @FXML public void handleCloseBtn(ActionEvent event) throws Exception {
        stage.close();
    }
}
