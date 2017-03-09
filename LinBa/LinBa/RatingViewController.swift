//
//  RatingViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 07.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class RatingViewController: UIViewController, UITextFieldDelegate, UIPickerViewDelegate, UIPickerViewDataSource {
    
    let rates = [0,1,2,3,4,5,6,7,8,9,10]
    
    @IBOutlet weak var vRate: UIAlertView!
    
    @IBOutlet weak var pickerView: UIPickerView!
    @IBOutlet weak var rateTextField: UITextField!
    
    let disposeBag = DisposeBag()
    
    var filmId: Int?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setRoundedBorder(withColor: UIColor(netHex: 0x2ED4C6))
        pickerView.isHidden = true
        rateTextField.delegate = self
        pickerView.delegate = self
        pickerView.dataSource = self
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    func setRoundedBorder(withColor: UIColor) {
        vRate.backgroundColor = withColor
        vRate.layer.cornerRadius = 8
        vRate.layer.borderWidth = 1
        vRate.layer.borderColor = withColor.cgColor
    }
    
    @IBAction func activatedComplete(_ sender: UIButton) {
        addRateToFilm()
    }
    
    func addRateToFilm() {
        ServerAPI.sharedInstance.addRateToFilm(filmId: filmId!, rate: Int(rateTextField.text!)!)
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (message) in
                self.showAlert(message: message!, success: true, title: "SUCCESS")
                
            }, onError: {(error) in
                if error is APIError {
                    let err = error as! APIError
                    self.showAlert(message: err.desc, success: false, title: "FAILED")
                }
                else {
                    self.addRateToFilm()
                }
            }).addDisposableTo(disposeBag)
    }
    
    func showAlert(message: String, success: Bool, title: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        if success {
            let okAction = UIAlertAction(title: "OK", style: .default) { (action) in
                self.dismiss(animated: false, completion: nil)
            }
            alert.addAction(okAction)
        }
        else {
            let cancelAction = UIAlertAction(title: "CANCEL", style: .cancel, handler: nil)
            alert.addAction(cancelAction)
        }
        self.present(alert, animated: true, completion: nil)
    }
  
    @IBAction func activatedCancel(_ sender: UIButton) {
        self.dismiss(animated: false, completion: nil)
    }
    
    func textFieldShouldBeginEditing(_ textField: UITextField) -> Bool {
        pickerView.isHidden = false
        return false
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return rates.count
    }
    
    func pickerView(_ pickerView: UIPickerView, attributedTitleForRow row: Int, forComponent component: Int) -> NSAttributedString? {
        let attributedString = NSAttributedString(string: String(rates[row]), attributes: [NSForegroundColorAttributeName : UIColor.white])
        return attributedString
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        rateTextField.text = String(rates[row])
        pickerView.isHidden = true
    }
    

    
    
}
