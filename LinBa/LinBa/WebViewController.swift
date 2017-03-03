//
//  WebViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 14.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class WebViewController: UIViewController {
    
    @IBOutlet weak var webView: UIWebView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loadYoutube(videoID: "0e71Y_3-dQs")
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    func loadYoutube(videoID:String) {
        guard
            let youtubeURL = URL(string: "https://www.youtube.com/embed/\(videoID)")
            else { return }
        webView.loadRequest( URLRequest(url: youtubeURL) )
    }
    
}
