//
//  SignInViewController.m
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import "SignInViewController.h"
#import "BINDatabaseHandler.h"

@interface SignInViewController ()

@end

@implementation SignInViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    NSLog(@"dudu");
    self.signButton.enabled = NO;
    [self.usernameTextField becomeFirstResponder];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/


- (IBAction)signButtonPressed:(UIButton *)sender {
    if(self.usernameTextField.text.length && self.passwordTextField.text.length){
        if([[BINDatabaseHandler databaseHandler] signinVerify:self.usernameTextField.text withPassword:self.passwordTextField.text]){
            if([self.usernameTextField.text isEqual: @"admin"]){
                
                [self performSegueWithIdentifier:@"adminSignIn" sender:self];
            }
            else{
                [self performSegueWithIdentifier:@"normalSignIn" sender:self];

            }
            NSLog(@"登录成功");
        }
        else{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                            message:@"登录失败！请检查你的用户名和密码是否正确。"
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil];
            [alert show];
        }
    }
}

- (IBAction)usernameEditingChanged:(UITextField *)sender
{
    [self checkLoginButtonEnabled];
}

- (IBAction)passwordEditingChanged:(UITextField *)sender
{
    [self checkLoginButtonEnabled];
    
}

- (void)checkLoginButtonEnabled
{
    if(self.usernameTextField.text.length && self.passwordTextField.text.length)
    {
        self.signButton.enabled = YES;
    }
    else
    {
        self.signButton.enabled = NO;
    }
    
}

@end
