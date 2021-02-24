# git突破单文件100M的限制

## Getting Started

1. ​            [Download](https://github.com/git-lfs/git-lfs/releases/download/v2.13.2/git-lfs-windows-v2.13.2.exe)            and install the Git command line extension. Once downloaded  and installed, set up Git LFS for your user account by running:          

   ```
   git lfs install
   ```

   You only need to run this once per user account.

2. In each Git repository where you want to use Git LFS,  select the file types you'd like Git LFS to manage (or directly edit  your .gitattributes). You can configure additional file extensions at  anytime.

   ```
   git lfs track "*.psd"
   ```

   Now make sure .gitattributes is tracked:

   ```
   git add .gitattributes
   ```

   Note that defining the file types Git LFS should track will not, by itself, convert any pre-existing files to Git LFS, such as  files on other branches or in your prior commit history. To do that, use the [git lfs migrate[1\]](https://github.com/git-lfs/git-lfs/blob/main/docs/man/git-lfs-migrate.1.ronn?utm_source=gitlfs_site&utm_medium=doc_man_migrate_link&utm_campaign=gitlfs) command, which has a range of options designed to suit various potential use cases.

3. There is no step three. Just commit and push to GitHub as you normally would; for instance, if your current branch is named `main`:

   ```
   git add file.psd
   git commit -m "Add design file"
   git push origin main
   ```

## Git LFS is an open source project

To file an issue or contribute to the project, head over [to the repository](https://github.com/git-lfs/git-lfs?utm_source=gitlfs_site&utm_medium=repo_link&utm_campaign=gitlfs)        or read our [guide to contributing](https://github.com/git-lfs/git-lfs/blob/main/CONTRIBUTING.md?utm_source=gitlfs_site&utm_medium=contributing_link&utm_campaign=gitlfs).

If you're interested in integrating Git LFS into another tool or product, you might want to read the        [API specification](https://github.com/git-lfs/git-lfs/blob/main/docs/api/README.md?utm_source=gitlfs_site&utm_medium=api_spec_link&utm_campaign=gitlfs)        or check out our [reference server implementation](https://github.com/git-lfs/lfs-test-server?utm_source=gitlfs_site&utm_medium=reference_servedr&utm_campaign=gitlfs).