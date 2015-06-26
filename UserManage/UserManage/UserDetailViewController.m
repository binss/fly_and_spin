//
//  UserDetailViewController.m
//  UserManage
//
//  Created by bin on 15/6/26.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import "UserDetailViewController.h"
#import "BINDatabaseHandler.h"

@interface UserDetailViewController ()

@end

@implementation UserDetailViewController
@synthesize userDetail;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    NSLog(@"%@", userDetail);
    username = [userDetail objectForKey:@"username"];
    [self.usernameLabel setText:username];
    [self.nameLabel setText:[userDetail objectForKey:@"name"]];
    [self.timeLabel setText:[userDetail objectForKey:@"time"]];

    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *path = [[paths objectAtIndex:0] stringByAppendingPathComponent:[NSString stringWithFormat:@"UserImage/%@.png", username]];
    UIImage *userImage = [UIImage imageWithContentsOfFile:path];
    if(userImage)
        [self.userImageView setImage:[UIImage imageWithContentsOfFile:path]];
    self.userImageView.userInteractionEnabled = YES;
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapUserImage:)];
    [singleTap setNumberOfTouchesRequired:1];
    [singleTap setNumberOfTapsRequired:1];
    [self.userImageView addGestureRecognizer:singleTap];
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

- (void)tapUserImage:(UITapGestureRecognizer*)tap
{
    NSLog(@"click userImage");
    [self openThePhotoAlbum];
}

#pragma mark 打开系统相册或照相机
- (void)openThePhotoAlbum
{
    //创建图片选取器对象
    UIImagePickerController * pickerViwController = [[UIImagePickerController alloc] init];
    /*
     图片来源
     UIImagePickerControllerSourceTypePhotoLibrary：表示显示所有的照片
     UIImagePickerControllerSourceTypeCamera：表示从摄像头选取照片
     UIImagePickerControllerSourceTypeSavedPhotosAlbum：表示仅仅从相册中选取照片。
     */
    pickerViwController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    
    //允许用户编辑图片 (YES可以编辑，NO只能选择照片)
    pickerViwController.allowsEditing = YES;
    
    //设置代理
    pickerViwController.delegate = self;
    
    [self presentViewController:pickerViwController animated:YES completion:nil];
}

#pragma mark 相册协议中方法，选中某张图片后调用方法
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    [self dismissViewControllerAnimated:YES completion:nil];
    
    //头像设置为选中的图片
    UIImage* image = [info objectForKey:@"UIImagePickerControllerEditedImage"];
    self.userImageView.image = image;
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    // 保存文件路径
    NSString *path = [[paths objectAtIndex:0] stringByAppendingPathComponent:[NSString stringWithFormat:@"UserImage/%@.png", username]];
    [UIImagePNGRepresentation(image)writeToFile:path atomically:YES];
}

- (IBAction)modifynameButtonPress:(UIButton *)sender {
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"修改昵称"
                                                    message:@"请输入新的昵称："
                                                   delegate:self
                                          cancelButtonTitle:@"cancel"
                                          otherButtonTitles:@"OK", nil];
    // 基本输入框，显示实际输入的内容
    alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    [alert show];
}

- (IBAction)startgameButtoPressed:(UIButton *)sender {
}

-(void)alertView:(UIAlertView*)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    //得到输入框
    UITextField *textfield = [alertView textFieldAtIndex:0];
    NSLog(@"new name:%@", textfield.text);
    [[BINDatabaseHandler databaseHandler] modifyName:textfield.text forUsername:username];
}
@end
